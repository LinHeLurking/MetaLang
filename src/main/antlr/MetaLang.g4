grammar MetaLang;
import CommonLexRules;

prog:    stat+ EOF? ;

eol: NEWLINE | (SEMICOLON NEWLINE?);

stat:    expr eol               # ExprStat
    |    ID ASSIGN expr eol     # AssignStat
    |    eol                    # BlankStat
    ;

expr:    expr MUL expr                 # MulExpr
    |    expr DIV expr                 # DivExpr
    |    expr ADD expr                 # AddExpr
    |    expr SUB expr                 # SubExpr
    |    NUM_LITERAL                   # NumLiteral
    |    ID                            # IdExpr
    |    LEFT_PAREN expr RIGHT_PAREN   # ParenExpr
    ;
