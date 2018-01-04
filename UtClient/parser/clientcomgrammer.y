%include
{
 #include <cassert>
 #include "clientparse.h"
 #include "commandlist.h"
 #define YYSTYPE const char
}

%syntax_error
{
	act->syntaxError();
}
%parse_accept 
{
  act->successfulParse();
}
%parse_failure  
{
  act->unsuccessfulParse();
}
%stack_overflow   
{
  act->stackOverflow();
}
%name ParseClient
%token_type {const char*}
%extra_argument {ClientParse* act}

start ::=  command . 
command ::= JAN NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::January, year, days);}
command ::= FEB NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::Febuary, year, days);}
command ::= MAR NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::March, year, days);}
command ::= APR NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::April, year, days);}
command ::= MAY NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::May, year, days);}
command ::= JUN NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::June, year, days);}
command ::= JUL NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::July, year, days);}
command ::= AUG NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::August, year, days);}
command ::= SEP NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::September, year, days);}
command ::= OCT NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::October, year, days);}
command ::= NOV NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::November, year, days);}
command ::= DEC NUM(year) HAS NUM(days) DAYS . {act->response(Cmd::December, year, days);}



