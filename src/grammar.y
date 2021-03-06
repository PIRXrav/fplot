%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "obj_handler.h"
  #include "fpcode.h"
  #include "ast_displayer.h"
  #include "ast_traversal.h"


  #include "utils/hashtable.h"

  #include <assert.h>

  int yyparse(AST_NODE **root);
  int yyerror(AST_NODE **root, char *s);
  int yylex();
%}
%code requires {
  #include "ast.h"
}


%debug
%define api.value.type {void *}

%parse-param {AST_NODE **root}

// union /!\


%token EQUAL

%token ENTIER
%left DOUBLEPT
%left PLUS MOINS
%left FOIS DIVISE
%left EQ NE LT LE GT GE

%token OPAR CPAR
%token BEG END
%token IF ELSIF ELSE
%token FOR WHILE
%token FUNC
%token RETURN
%token NEW

%token COMMA
%token PTCOMMA

%token VAR
%token STRING


%start ROOT

%%

ROOT: statements                        {
                                          *root = $1;
                                        }
/* Instrucions */
statements
  : statement statements                { $$ = AST_NODE_STAT_Create($2/*next*/,$1); }
  | %empty                              { $$ = NULL;/* *** EOP *** */   }


statement
  : statement_affectation               { $$ = $1; }
  | statement_condition                 { $$ = $1; }
  | statement_while                     { $$ = $1; }
  | statement_expression                { $$ = AST_NODE_PCODE_Create(PC_CreatePop(), $1, NULL);}
  | statement_compound                  { $$ = $1; }
  | statement_return                    { $$ = $1; }

statement_compound
  : BEG statements END                  { $$ = $2; }

statement_expression
  : expr PTCOMMA                        { $$ = $1; }
  | PTCOMMA

statement_affectation
  : var_dst EQUAL expr PTCOMMA          { $$ = AST_NODE_PCODE_Create(PC_CreateStore((char *)$1), $3, NULL); }

statement_condition
  : IF OPAR expr CPAR BEG statement END
    { $$ = AST_NODE_IF_Create($3, $6, NULL); }
  | IF OPAR expr CPAR BEG statement END ELSE BEG statement END
    { $$ = AST_NODE_IF_Create($3, $6, $10); }

statement_while
  : WHILE OPAR expr CPAR BEG statement END { $$ = AST_NODE_WHILE_Create($3, $6); }

statement_return
  : RETURN return_value PTCOMMA         { $$ = AST_NODE_PCODE_Create(PC_CreateReturn(), $2, NULL); }

return_value
  : %empty                              { $$ = AST_NODE_PCODE_Create(PC_CreatePushCst(NULL), NULL, NULL); }
  | expr                                { $$ = $1; }

expr
  : var_src                             { $$ = $1; }
  | expr DOUBLEPT expr                  { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__ADD__), $1, $3); printf("LISTE : TODO\n"); }
  | expr PLUS expr                      { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__ADD__), $1, $3); }
  | expr MOINS expr                     { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__SUB__), $1, $3); }
  | expr FOIS expr                      { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__MUL__), $1, $3); }
  | expr DIVISE expr                    { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__FDV__), $1, $3); }
  | expr EQ expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__EQ__), $1, $3); }
  | expr NE expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__NE__), $1, $3); }
  | expr LT expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__LT__), $1, $3); }
  | expr GT expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__GT__), $1, $3); }
  | expr LE expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__LE__), $1, $3); }
  | expr GE expr                        { $$ = AST_NODE_PCODE_Create(PC_CreateApply(__GE__), $1, $3); }
  | OPAR expr CPAR                      { $$ = $2; }
  | var_src OPAR expr_list CPAR            { $$ = AST_NODE_FUNC_CALL_Create($1/* name */, $3/* args*/ ); }
  | FUNC OPAR name_list CPAR BEG statements END
                                        { $$ = AST_NODE_FUNC_DEC_Create($3/* args*/, $6/*code */);}
  | NEW VAR OPAR CPAR                   { $$ = AST_NODE_PCODE_Create(PC_CreateClassInit((char *)$2), NULL, NULL); }

expr_list
  : expr_list_not_empty                 { $$ = $1; }
  | %empty                              { $$ = NULL; }

expr_list_not_empty
  : expr COMMA expr_list_not_empty      { $$ = $1; AST_NODE_CAST_PCODE($$)->arg1 = $3; /* link args reverse order */}
  | expr                                { $$ = $1; }

var_src
  : VAR                                 { $$ = AST_NODE_PCODE_Create(PC_CreateLoad((char *)$1), NULL, NULL);}
  | ENTIER                              { $$ = AST_NODE_PCODE_Create(PC_CreatePushCst($1), NULL, NULL); }
  | STRING                              { $$ = AST_NODE_PCODE_Create(PC_CreatePushCst($1), NULL, NULL); }

var_dst
  : VAR                                 { $$ = $1; }

name_list
  : name_list_not_empty                 { $$ = $1; }
  | %empty                              { $$ = NULL; }

name_list_not_empty
  : name_list_not_empty COMMA VAR       { $$ = AST_NODE_PCODE_Create(PC_CreateStore((char *)$3), $1, NULL); }
  | VAR                                 { $$ = AST_NODE_PCODE_Create(PC_CreateStore((char *)$1), NULL, NULL); }



%%

int yyerror(AST_NODE **root, char *s){
    printf("yyerror : %s || tree : %p\n", s, root);
    AST_DISPLAY_Text(*root, 0);
    exit(1);
}
