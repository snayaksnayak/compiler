/* My own C compiler */
/* Date: 01 Oct 2007 */
/* Author: Srinivas Nayak */
/* Compile using gcc */

/* This code is distributed under the GPL License. */
/* For more info check: */
/* http://www.gnu.org/copyleft/gpl.html */


/*******************************************************************************
* This program comprises of a lexical analyzer along with a syntax analyzer
* for Programming Language C (C89) as defined in K&R book second edition.
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
char stack[100];  //stores temporarily the string of character
		  //being processed by lexical analyzer.
int tos=-1;  //top of the stack.
FILE *f;  //file pointer referring to the source file.
long pos=1;     //only used in get_next_token function
		//to count a '\n' in the source file as a new line,
		//only once, even if we encounter the same
		//'\n' character many times while moving forward
		//and backword,passing over it.
int line_number=1; //this is used to hold the line number of
		   //source file at which the compiler failed (or sucseed).

int identifier_flag=0;  //become true only when lexical analyzer
			//found an identifier.
int integer_constant_flag=0; //same as above; name is self explanatory.
int floating_constant_flag=0;
int character_constant_flag=0;
int string_flag=0;

void reset_flags();//clear the flags.

//prints the data processed by parser till now
void print_processed_data(long start_pos, long end_pos);

//each of these below functions are utility functions
//which helps lexical analyzer.
int isdigit(char);// returns true if the character provided to it is a digit.
int isletter(char);// returns true if the character provided to it is a letter.
int isspecial(char);// returns true if the character provided to it
		    // is a character other than digit or letter.

//stack utility functions.
void push(char ch);
void pop();

void flush(); //flushes our stack.
void token_error();//prints error message if lexical analyzer
		   //find some non-recognizable token
int get_next_token();   //our LEXICAL ANALYZER. It scans the next token
			//in the source file and saves it in stack
			//and returns true if it is a valid C token.
int check_terminal(char *terminal);//this function when provided a
		//C keyword/token/terminal symbol, returns true or false
		//based on whether lexical analyzer found the same
		//keyword/token/terminal symbol as provided or not.
		//It compares the current stack content to the provided
		//string to see if they are the same.

//these below are the functions each corresponding to a NONterminal
//in C grammar as defined in C89.
int translation_unit();
int external_declaration();
int function_definition();
int declaration();
int declaration_list();
int declaration_specifiers();
int storage_class_specifier();
int type_specifier();
int type_qualifier();
int struct_or_union_specifier();
int struct_or_union();
int struct_declaration_list();
int init_declarator_list();
int init_declarator();
int struct_declaration();
int specifier_qualifier_list();
int struct_declarator_list();
int struct_declarator();
int enum_specifier();
int enumerator_list();
int enumerator();
int declarator();
int direct_declarator();
int pointer();
int type_qualifier_list();
int parameter_type_list();
int parameter_list();
int parameter_declaration();
int identifier_list();
int initializer();
int initializer_list();
int type_name();
int abstract_declarator();
int direct_abstract_declarator();
int typedef_name();
int statement();
int labeled_statement();
int expression_statement();
int compound_statement();
int statement_list();
int selection_statement();
int iteration_statement();
int jump_statement();
int expression();
int assignment_expression();
int assignment_operator();
int conditional_expression();
int constant_expression();
int logical_OR_expression();
int logical_AND_expression();
int inclusive_OR_expression();
int exclusive_OR_expression();
int AND_expression();
int equality_expression();
int relational_expression();
int shift_expression();
int additive_expression();
int multiplicative_expression();
int cast_expression();
int unary_expression();
int unary_operator();
int postfix_expression();
int primary_expression();
int argument_expression_list();
int constant();

//these below are the functions each corresponding to a
//terminal/token in C grammar(C89).
int identifier();
int string();
int integer_constant();
int floating_constant();
int enumeration_constant();
int character_constant();

//each of these below defines corresponds to a keyword in
//C grammar(C89). These have been defined to a function call,
//which when provided the actual C keyword, returns true or false
//based on whether lexical analyzer found the same keyword as provided or not.
#define VOID (check_terminal("void"))
#define AUTO (check_terminal("auto"))
#define REGISTER (check_terminal("register"))
#define STATIC (check_terminal("static"))
#define EXTERN (check_terminal("extern"))
#define TYPEDEF (check_terminal("typedef"))
#define CHAR (check_terminal("char"))
#define SHORT (check_terminal("short"))
#define INT (check_terminal("int"))
#define LONG (check_terminal("long"))
#define FLOAT (check_terminal("float"))
#define DOUBLE (check_terminal("double"))
#define SIGNED (check_terminal("signed"))
#define UNSIGNED (check_terminal("unsigned"))
#define CONST (check_terminal("const"))
#define VOLATILE (check_terminal("volatile"))
#define STRUCT (check_terminal("struct"))
#define UNION (check_terminal("uion"))
#define ENUM (check_terminal("enum"))
#define CASE (check_terminal("case"))
#define DEFAULT (check_terminal("default"))
#define IF (check_terminal("if"))
#define ELSE (check_terminal("else"))
#define SWITCH (check_terminal("switch"))
#define WHILE (check_terminal("while"))
#define DO (check_terminal("do"))
#define FOR (check_terminal("for"))
#define GOTO (check_terminal("goto"))
#define CONTINUE (check_terminal("continue"))
#define BREAK (check_terminal("break"))
#define RETURN (check_terminal("return"))

//each of these below defines corresponds to a terminal symbol/operator
//in C grammar(C89). These have been defined to a function call,
//which when provided the actual C terminal symbol/operator,
//returns true or false based on whether lexical analyzer found
//the same terminal symbol/operator as provided or not.
//Each group of defines has been listed in decreasing order of precedence.
//In a group, allhave the same precedence.
//------------------start-----------------
#define LEFT_PARENTHESIS (check_terminal("("))
#define RIGHT_PARENTHESIS (check_terminal(")"))
#define LEFT_BRACKET (check_terminal("["))
#define RIGHT_BRACKET (check_terminal("]"))
#define ARROW (check_terminal("->"))
#define DOT (check_terminal("."))
//-------------------------------
#define NOT (check_terminal("!"))
#define TILDE (check_terminal("~"))
#define PLUS_PLUS (check_terminal("++"))
#define MINUS_MINUS (check_terminal("--"))
#define PLUS (check_terminal("+"))
#define MINUS (check_terminal("-"))
#define ASTERISK (check_terminal("*"))
#define AMPERSAND (check_terminal("&"))
//(type)
#define SIZEOF (check_terminal("sizeof"))
//-----------------------------------
//*
#define FRONT_SLASH (check_terminal("/"))
#define PERCENTAGE (check_terminal("%"))
//------------------------------------
//+
//-
//------------------------------------
#define LESSTHAN_LESSTHAN (check_terminal("<<"))
#define GREATERTHAN_GREATERTHAN (check_terminal(">>"))
//------------------------------------
#define LESSTHAN (check_terminal("<"))
#define LESSTHAN_EQUAL (check_terminal("<="))
#define GREATERTHAN (check_terminal(">"))
#define GREATERTHAN_EQUAL (check_terminal(">="))
//--------------------------------------
#define EQUAL_EQUAL (check_terminal("=="))
#define NOT_EQUAL (check_terminal("!="))
//-------------------------------------
//&
//-------------------------------------
#define CARAT (check_terminal("^"))
//----------------------------------
#define PIPE (check_terminal("|"))
//--------------------------------
#define AMPERSAND_AMPERSAND (check_terminal("&&"))
//------------------------------------
#define PIPE_PIPE (check_terminal("||"))
//-----------------------------------
//both make a single operator
#define QUESTION_MARK (check_terminal("?"))
#define COLON (check_terminal(":"))
//----------------------------------
#define EQUAL (check_terminal("="))
#define PLUS_EQUAL (check_terminal("+="))
#define MINUS_EQUAL (check_terminal("-="))
#define ASTERISK_EQUAL (check_terminal("*="))
#define FRONTSLASH_EQUAL (check_terminal("/="))
#define PERCENTAGE_EQUAL (check_terminal("%="))
#define AMPERSAND_EQUAL (check_terminal("&="))
#define CARAT_EQUAL (check_terminal("^="))
#define PIPE_EQUAL (check_terminal("|="))
#define LESSTHAN_LESSTHAN_EQUAL (check_terminal("<<="))
#define GREATERTHAN_GREATERTHAN_EQUAL (check_terminal(">>="))
//----------------------------------
#define COMMA (check_terminal(","))
//--------------end-----------------

//following are not operators but terminal symbols
#define LEFT_BRACE (check_terminal("{"))
#define RIGHT_BRACE (check_terminal("}"))
#define SEMICOLON (check_terminal(";"))
#define ELLIPSIS (check_terminal("..."))

void reset_flags()
{
//clear all the flags.
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
}

int check_terminal(char *terminal)
{
    int retval;
    long pos;   //stores the current offset of the source file
		//upon entering to this function.
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1) //if the lexical analyzer
						      //found a valid C token.
    {
	if(strcmp(terminal,stack)==0) //compare the string in the stack
		//which has been stored by lexical analyzer
		//upon finding the token with the string passed to
		//this function. If they are equal go into.
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush(); // clean the stack.
	    reset_flags(); //reset all the flags.
	    return 1;   //return true to caller saying that
			//caller got the token which one he wanted.
	}
        else //if caller didn't get what he wanted,
        {
	    flush(); //still clean the stack,because some token will be there
		     //although caller didn't get what he wanted.
	    fseek(f,pos,SEEK_SET); //since caller didn't get what he wanted,
			//the token found will not be processed,so go back to
			//the position from where we have started looking for
			//next token.
	    reset_flags(); //still clean the flags, because some token of
		//some type was found and any one of these may have been set.
     	    return 0; //return failure notice to the caller.
        }

    }
    else //if lexical analyser got an invalid C token or it got EOF.
    {
	    flush();    //make sure that the stack is clean
			//before leaving this function.
	    fseek(f,pos,SEEK_SET); //before returning,make sure that
			//we don't disturb the position till which processiong
			//has been done. That is, return without disturbing
			//the file position from where we have started
			//while entering to this function.
	    reset_flags(); //also make sure no flag is set.
	    return 0; //return failure notice to the caller.
    }
}

int identifier()
{
//all the comments of check_terminal function (above) is valid.
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (identifier_flag == 1) //if an identifier is found
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush();
	    reset_flags();
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
	reset_flags();
       	    return 0;
	}
    }
    else
    {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
	return 0;
    }

}
int string()
{
//all the comments of check_terminal function (above) are valid here.
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (string_flag == 1)//if a C string is found.
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush();
reset_flags();
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
       	    return 0;
	}
    }
    else
    {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
	return 0;
    }

}
int integer_constant()
{
//all the comments of check_terminal function (above) are valid here.
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (integer_constant_flag == 1)//if an integer constant is found.
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush();
reset_flags();
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
       	    return 0;
	}
    }
    else
    {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
	return 0;
    }
}
int floating_constant()
{
//all the comments of check_terminal function (above) are valid here.
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (floating_constant_flag == 1)//if a floating constant is fount.
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush();
reset_flags();
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
       	    return 0;
	}
    }
    else
    {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
	return 0;
    }
}
int character_constant()
{
//all the comments of check_terminal function (above) are valid here.
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (character_constant_flag == 1)//if a character constant is found.
	{
//	printf("\n-----%s-----\n\n",stack);
	    flush();
reset_flags();
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
reset_flags();
       	    return 0;
	}
    }
    else
    {
	    flush();
	    fseek(f,pos,SEEK_SET);
	reset_flags();
	return 0;
    }
}
int enumeration_constant()
{
//all the comments of check_terminal function (above) are valid here.
	flush();
	return 0;
}

int main(int argc,char **argv)
{
int retval;
if(argc!=2) //if a source file name is not given, exit.
  exit(0);

f=fopen(argv[1],"r"); //open the source file to read.

 if(f==NULL)
 {
  printf("error");
  exit(0);
 }
translation_unit(); //check if the source file contains a C translation unit.
return 0;
}

//our lexical analyzer.
int get_next_token()
{
	char ch=0; //stores each character read from the source file.
	int state=0; //current state of the state machine.
	reset_flags(); //make sure no flag is set before we proceed.
	s0:
	    state = 0; // we are in state 0.
	    ch=getc(f); //get the next character from the source file.
		if(ch==EOF) //if we reach at EOF then return to the caller
			    //saying so.
		    return EOF;
	    if(!(ch==' ' || ch=='\n' || ch =='\t' || ch ==0x0d))//if we get
			//a non-space character, push it into the stack.
	    push(ch);

	    if(ch==' ' || ch=='\n' || ch =='\t' || ch ==0x0d) //if we get
			//a space, goto state 0.
	    {

/* This below code(temporary) is to report line number where error found */
		if (ch =='\n')
		{
		    if(ftell(f)>pos)
		    {
			pos=ftell(f);
			line_number++;
		    }
		}
/* This above code(temporary) is to report line number where error found */

		goto s0;//if we get a space, goto state 0.
	    }
	    else if(isletter(ch) || ch=='_')
	    {
		goto s1; //we may get an identifier, so go to state 1.
	    }
	    else if(ch=='.')
	    {
		goto s3; //we may now get a floating point constant,
			 //so go to state 3.
	    }
	    else if(isdigit(ch))
	    {
		goto s2; //it can be an integer constant,so go to state 2.
	    }
	    else if(ch=='\'')
	    {
		goto s4; //may be a character constant,so go to state 4.
	    }
	    else if(ch=='\"')
	    {
		goto s8; //we may get a string constant,so go to state 8.
	    }
	    else if(isspecial(ch)) //if non of the above, it may be a
				   //C operator or a C terminal.
	    {
		goto s10; //so go to state 10.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s1: //final state for identifier.
	    state = 1;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || isdigit(ch) || ch == '_')
	    {
		goto s1; //we may get an identifier.
            }
	    else
	    {
	        goto END; // else go to END to see what we get.
	    }
	s2: //final state for integer constant
	    state = 2;
	    ch=getc(f);
	    push(ch);
	    if(ch == '.')
	    {
		goto s3; //we may get a floating point constant,
			 //so go to state 3.
	    }
	    else if(isdigit(ch))
	    {
		goto s2; //it may be an integer constant.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s3: //final state for dot operator (used with structures).
	    state = 3;
	    ch=getc(f);
	    push(ch);
	    if(isdigit(ch))
	    {
		goto s2; //we may get an floating constant,so go to state 2.
	    }
	    else if(ch == '.')
	    {
		goto s33;//we may get an ellipsis.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s4:
	    state = 4;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || (isspecial(ch) && ch !='\'' && ch !='\\')
			    || isdigit(ch))
	    {
		goto s6; //this may be the character of
			 //that character constant, so go to state 6.
	    }
	    else if(ch == '\\')
	    {
		goto s5; //it could be an escape character, so go to state 5.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s5:
	    state = 5;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || isspecial(ch) || isdigit(ch))
	    {
		goto s6; //it could be the character of that escape character,
			 //so go to state 6.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s6:
	    state = 6;
	    ch=getc(f);
	    push(ch);
	    if(ch == '\'')
	    {
		goto s7; //we might have got a (escape)character constant,
			 //so go to state 7.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s7: //final state for character constant
	    state = 7;
	    goto END; //go to END to see what we get.
	s8:
	    state = 8;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || (isspecial(ch) && ch != '\"') || isdigit(ch))
	    {
		goto s8; //could be the character of that string constant,
			 //so go to state 8.
	    }
	    else if(ch == '\"')
	    {
		goto s9; // we might have got a string constant.
	    }
	    else
	    {
		goto END; // else go to END to see what we get.
	    }
	s9: //final state of string constant.
	    state = 9;
	    goto END; // go to END to see what we get.
	s10: //final state for symbols(eg. parenthesis etc.)
	    state = 10;
		fseek(f,-1,SEEK_CUR); //we are in state 10,it means we
		//consumed a character which might be a part of an operator
		//or a special symbol (eg. left parenthesis etc.) which
		//we have already consumed. So go back one character
		//and move forward to see what it is...
		pop();  //since we are going back one character,
			//we must pop it from the stack, because before we know
			//what character it is, we have put it into the stack.
	    ch=getc(f);
	    push(ch);
		if(ch=='-')
		    goto s11;
		else if(ch=='!')
		    goto s14;
		else if(ch=='~')
		    goto s16;
		else if(ch=='+')
		    goto s17;
		else if(ch=='*')
		    goto s19;
		else if(ch=='/')
		    goto s20;
		else if(ch=='%')
		    goto s21;
		else if(ch=='<')
		    goto s22;
		else if(ch=='>')
		    goto s24;
		else if(ch=='=')
		    goto s26;
		else if(ch=='&')
		    goto s27;
		else if(ch=='^')
		    goto s29;
		else if(ch=='|')
		    goto s30;
		else if(ch==',')
		    goto s32;
		else
		    goto END; // else go to END to see what we get.
	    s11: //final state for -
	        state = 11;
	        ch=getc(f);
	        push(ch);
		if(ch=='-')
		    goto s12;
		else if(ch=='=')
		    goto s15;
		else if(ch=='>')
		    goto s13;
		else
		    goto END; // else go to END to see what we get.
	    s12: //final state for --
	        state = 12;
		    goto END; // go to END to see what we get.
	    s13: //final state for ->
	        state = 13;
		    goto END; // go to END to see what we get.
	    s14: //final state for !
	        state = 14;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s15: //final state for !=,+=,-=,*=,etc.
	        state = 15;
		    goto END; // go to END to see what we get.
	    s16: //final state for ~
	        state = 16;
		    goto END; // go to END to see what we get.
	    s17: //final state for +
	        state = 17;
	        ch=getc(f);
	        push(ch);
		if(ch=='+')
		    goto s18;
		else if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s18: //final state for ++
	        state = 18;
		    goto END; // go to END to see what we get.
	    s19: //final state for *
	        state = 19;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s20: //final state for /
	        state = 20;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s21: //final state for %
	        state = 21;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s22: //final state for <
	        state = 22;
	        ch=getc(f);
	        push(ch);
		if(ch=='<')
		    goto s23;
		else if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s23: //final state for <<
	        state = 23;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s24: //final state for >
	        state = 24;
	        ch=getc(f);
	        push(ch);
		if(ch=='>')
		    goto s25;
		else if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s25: //final state for >>
	        state = 25;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s26: //final state for =
	        state = 26;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s27: //final state for &
	        state = 27;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else if(ch=='&')
		    goto s28;
		else
		    goto END; // else go to END to see what we get.
	    s28: //final state for &&
	        state = 28;
		    goto END; // go to END to see what we get.
	    s29: //final state for ^
	        state = 29;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END; // else go to END to see what we get.
	    s30: //final state for |
	        state = 30;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else if(ch=='|')
		    goto s31;
		else
		    goto END; // else go to END to see what we get.
	    s31: //final state for ||
	        state = 31;
		    goto END; // go to END to see what we get.
	    s32: //final state for ,
	        state = 32;
		    goto END; // go to END to see what we get.
	s33:
		state = 33;
	        ch=getc(f);
	        push(ch);
		if(ch=='.')
		    goto s34;// we may get an ellipsis.
		else
		    goto END; // go to END to see what we get.
	s34: //final state for ...(ellipsis)
		state = 34;
		    goto END; // go to END to see what we get.

	END:
	    if(!(state==7 //after coming to this state, we directly came to END,
			  //so no extra character has been consumed by
			  //the lexical analyzer and also no extra character
			  //pused in to stack, so for this case,we need not
			  //go one character back as well as
			  //need not pop the stack.

		|| state==9 //same for this case

		|| state==10 //when we reached state 10, we immediately
			//went one character back and then we lookforward
			//for a character which may be either an operator
			//or a symbol. So when we reached END,
			//it is because we got a symbol,and itis not
			//a C operator,so we have that symbol on the stack
			//and we have already consumed it knowingly,
			//so no need to regret,no need to go back one character
			//and no need to pop the stack.

		|| state==12 //same as case of state 7, and also it is same
			     //for rest of the states listed here.
		|| state==13
		|| state==15
		|| state==16
		|| state==18
		|| state==28
		|| state==31
		|| state==32
		|| state==34
		))
	    {
		fseek(f,-1,SEEK_CUR); //go back one character
		pop(); //also pop that unwanted charcter from the stack
	    }

	    if(state==1 // we got an identifier.
		|| state==2 //we got either an integer constant
			    //or a floating point constant
		|| state==3 //we got dot(.) operator
		|| state==7 //we got a character constant
		|| state==9 //we got a string constant
		|| state==10 //we got a special symbol (eg. parenthesis etc.)
		|| (state>=11 && state<=32) //we got an operator
		|| state==34 //we got an ellipsis(...)
	      )
	    {
		switch(state)
		{
		    case 1:
			if (
			   (strcmp(stack,"void")!=0)
			&& (strcmp(stack,"auto")!=0)
			&& (strcmp(stack,"register")!=0)
			&& (strcmp(stack,"static")!=0)
			&& (strcmp(stack,"extern")!=0)
			&& (strcmp(stack,"typedef")!=0)
			&& (strcmp(stack,"char")!=0)
			&& (strcmp(stack,"short")!=0)
			&& (strcmp(stack,"int")!=0)
			&& (strcmp(stack,"long")!=0)
			&& (strcmp(stack,"double")!=0)
			&& (strcmp(stack,"float")!=0)
			&& (strcmp(stack,"signed")!=0)
			&& (strcmp(stack,"unsigned")!=0)
			&& (strcmp(stack,"const")!=0)
			&& (strcmp(stack,"volatile")!=0)
			&& (strcmp(stack,"struct")!=0)
			&& (strcmp(stack,"union")!=0)
			&& (strcmp(stack,"enum")!=0)
			&& (strcmp(stack,"case")!=0)
			&& (strcmp(stack,"default")!=0)
			&& (strcmp(stack,"if")!=0)
			&& (strcmp(stack,"else")!=0)
			&& (strcmp(stack,"switch")!=0)
			&& (strcmp(stack,"while")!=0)
			&& (strcmp(stack,"do")!=0)
			&& (strcmp(stack,"for")!=0)
			&& (strcmp(stack,"goto")!=0)
			&& (strcmp(stack,"continue")!=0)
			&& (strcmp(stack,"break")!=0)
			&& (strcmp(stack,"return")!=0)
			&& (strcmp(stack,"sizeof")!=0)
			)
			{ // filter the keywords out, so that we only get
			  //user defind identifiers.
			identifier_flag=1; //we got an user defined identifier
		        //printf("%s ","id");
			}
			break;
		    case 2:
			{
			integer_constant_flag=1; //either we got an
						 //integer constant
			floating_constant_flag=1; //or we got a
						  //floating constant
		        //printf("%s ","int_const");
			}
			break;
		    case 3://we got a dot operator
		        //printf("%s ","op");
			break;
		    case 7:
			{
			character_constant_flag=1; //we got a character constant
		        //printf("%s ","ch_const");
			}
			break;
		    case 9:
			{
			string_flag=1; //we got a string constant
		        //printf("%s ","st_const");
			}
			break;
		    case 10: //we got a special symbol (eg. parenthesis etc.)
		    case 34: //we got an ellipsis symbol
		        //printf("%s ","symbol");
			break;
		    default: //we got an operator
		        //printf("%s ","op");
			break;
		}
	    }
	    else //something is wrong! we got an invalid C token,
		 //return a failure notice.
	    {
		return 0;
	    }
return 1; // if we reach here, that means, we got a valid C token,
	  //return a success notice, and the token is in the stack!
}

void token_error()
{
	printf("%25s","error at : ");
	flush();
	printf("\n");
}

int isdigit(char ch)
{
	if(ch >= 48 && ch <= 57) // if it is a digit from 0-9
	    return 1;
	else
	    return 0;
}

int isletter (char ch)
{
	if((ch >= 'A' && ch <=  'Z') || (ch >= 'a' && ch <= 'z') )
	    return 1; //if it is an english letter
	else
	    return 0;
}

int isspecial (char ch)
{
	if(!(isdigit(ch) || isletter(ch)))
	    return 1; //if it is neither an english letter nor a digit
	else
	    return 0;
}

void push(char ch)
{
	if(tos==98)
	   exit(0);
	tos++;
	stack[tos]=ch;
/* temporary*/
	stack[tos+1]='\0'; //put a null character on top of the stack,
			//so that we can treat the stack content as a string.
}

void pop()
{
	if(tos==-1)
	   exit(0);
	tos--;
/* temporary*/
	stack[tos+1]='\0'; //put a null character on top of the stack,
			//so that we can treat the stack content as a string.
}

void flush()
{
	//stack[tos+1]='\0';
	//printf("%s",stack);
	tos=-1;
	stack[tos+1]='\0'; //put a null character on top of the stack,
			//so that we can treat the stack content as a string.
}

/*******************************************
Following are the functions each corresponding to one production
of the C grammar as given in K&R book second edition.
The name of the functions are same as the name of the productions
or non-terminals.
*******************************************/

int translation_unit()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f); //store the position of the file
			   //before going to check for external_declaration.
        if (external_declaration())
	{
	goto s1; //if found, go to state 1 to look for more repeatation.
	}

	fseek(f,pos_s0,SEEK_SET); //if we reach here,it means
			//we didn't get an external_declarateion,
			//so go back to the initial position of the file
			//at the time of entering to this state.
	goto END; //and go to END to report the status of failure
		  //or success to the caller.
s1:
	state = 1;
	pos_s1 = ftell(f); // store the position of the file
			   //before going to check for external_declaration.
        if (external_declaration())
	{
	goto s1; //if one more found, go to state 1 to look for
		 //more repeatation.
	}

	fseek(f,pos_s1,SEEK_SET);//if we reach here,it means we didn't get
				 //any more external_declarateion, so go back
				 //to the initial position of the file at the
				 //time of entering to this state.
	goto END; //and go to END to report the status of failure
		  //or success to the caller.
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => translation_unit found");
		print_processed_data(pos_s0,ftell(f));
                printf("\nTranslation_unit found");
		printf(" at line number %d",line_number);
		printf("\nTotal number of characters processed %d",pos_s1);
                printf("\n");
                return 1; //if we are having a state 1, it means we found
			  //a translation_unit, so return success.
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => translation_unit failed");
		printf("( at line number %d )",line_number);
                printf("\n");
                return 0; //if we reach here, it means we didn't find
			  //a translation_unit, so return failure.
}
int external_declaration()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (declaration())
                {
                printf(") => external_declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (function_definition())
                {
                printf(") => external_declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => external_declaration failed");
                printf("\n");
                return 0;
}
int function_definition()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (declaration_specifiers()||1)
	if (declarator())
	if (declaration_list()||1)
	if (compound_statement())
                {
                printf(") => function_definition found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => function_definition failed");
                printf("\n");
                return 0;
}
int declaration()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (declaration_specifiers())
	if (init_declarator_list()||1)
	if (SEMICOLON)
                {
                printf(") => declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => declaration failed");
                printf("\n");
                return 0;
}
int declaration_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (declaration())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (declaration())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => declaration_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => declaration_list failed");
                printf("\n");
                return 0;
}
int declaration_specifiers()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (storage_class_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (type_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
        if (storage_class_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (type_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => declaration_specifiers found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => declaration_specifiers failed");
                printf("\n");
                return 0;
}
int storage_class_specifier()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (AUTO)
                {
                printf(") => storage_class_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (REGISTER)
                {
                printf(") => storage_class_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (STATIC)
                {
                printf(") => storage_class_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (EXTERN)
                {
                printf(") => storage_class_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (TYPEDEF)
                {
                printf(") => storage_class_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => storage_class_specifier failed");
                printf("\n");
                return 0;
}
int type_specifier()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (VOID)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (CHAR)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (SHORT)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (INT)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LONG)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (FLOAT)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (DOUBLE)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (SIGNED)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (UNSIGNED)
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (struct_or_union_specifier())
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (enum_specifier())
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (typedef_name())
                {
                printf(") => type_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => type_specifier failed");
                printf("\n");
                return 0;
}
int type_qualifier()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (CONST)
                {
                printf(") => type_qualifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (VOLATILE)
                {
                printf(") => type_qualifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => type_qualifier failed");
                printf("\n");
                return 0;
}
int struct_or_union_specifier()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (struct_or_union())
	if (identifier()||1)
	if (LEFT_BRACE)
	if (struct_declaration_list())
	if (RIGHT_BRACE)
                {
                printf(") => struct_or_union_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (struct_or_union())
	if (identifier())
                {
                printf(") => struct_or_union_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => struct_or_union_specifier failed");
                printf("\n");
                return 0;
}
int struct_or_union()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (STRUCT)
                {
                printf(") => struct_or_union found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (UNION)
                {
                printf(") => struct_or_union found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => struct_or_union failed");
                printf("\n");
                return 0;
}
int struct_declaration_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (struct_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
        if (struct_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => struct_declaration_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => struct_declaration_list failed");
                printf("\n");
                return 0;
}
int init_declarator_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (init_declarator())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && init_declarator())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => init_declarator_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => init_declarator_list failed");
                printf("\n");
                return 0;
}
int init_declarator()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (declarator())
	if (EQUAL)
	if (initializer())
                {
                printf(") => init_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (declarator())
                {
                printf(") => init_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => init_declarator failed");
                printf("\n");
                return 0;
}
int struct_declaration()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (specifier_qualifier_list())
	if (struct_declarator_list())
	if (SEMICOLON)
                {
                printf(") => struct_declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => struct_declaration failed");
                printf("\n");
                return 0;
}
int specifier_qualifier_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (type_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
        if (type_specifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => specifier_qualifier_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => specifier_qualifier_list failed");
                printf("\n");
                return 0;
}
int struct_declarator_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (struct_declarator())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && struct_declarator())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => struct_declaratoe_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => struct_declarator_list failed");
                printf("\n");
                return 0;
}
int struct_declarator()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (declarator()||1)
	if (COLON)
	if (constant_expression())
                {
                printf(") => struct_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (declarator())
                {
                printf(") => struct_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => struct_declarator failed");
                printf("\n");
                return 0;
}
int enum_specifier()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (ENUM)
	if (identifier()||1)
	if (LEFT_BRACE)
	if (enumerator_list())
	if (RIGHT_BRACE)
                {
                printf(") => enum_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (ENUM)
	if (identifier())
                {
                printf(") => enum_specifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => enum_specifier failed");
                printf("\n");
                return 0;
}
int enumerator_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (enumerator())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && enumerator())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => enumerator_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => enumerator_list failed");
                printf("\n");
                return 0;
}
int enumerator()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (identifier())
	if (EQUAL)
	if (constant_expression())
                {
                printf(") => identifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (identifier())
                {
                printf(") => identifier found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => identifier failed");
                printf("\n");
                return 0;
}
int declarator()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (pointer()||1)
	if (direct_declarator())
                {
                printf(") => declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => declarator failed");
                printf("\n");
                return 0;
}
int direct_declarator()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (identifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (LEFT_PARENTHESIS && declarator() && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (LEFT_BRACKET && (constant_expression()||1) && RIGHT_BRACKET)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (LEFT_PARENTHESIS && parameter_type_list() && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (LEFT_PARENTHESIS && (identifier_list()||1) && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => direct_declarator found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => direct_declarator failed");
                printf("\n");
                return 0;
}
int pointer()
{
    long pos_s0,pos_s1;
    int state;
		printf("(");
		printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (ASTERISK && (type_qualifier_list()||1))
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
        if (ASTERISK && (type_qualifier_list()||1))
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => pointer found");
		print_processed_data(pos_s0,ftell(f));
		printf("\n");
		return 1;
		}
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => pointer failed");
                printf("\n");
                return 0;

}
int type_qualifier_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (type_qualifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => type_qualifier found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => type_qualifier failed");
                printf("\n");
                return 0;

}
int parameter_type_list()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (parameter_list())
	if (COMMA)
	if (ELLIPSIS)
                {
                printf(") => parameter_type_list found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (parameter_list())
                {
                printf(") => parameter_type_list found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => parameter_type_list failed");
                printf("\n");
                return 0;
}
int parameter_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (parameter_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && parameter_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => parameter_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => parameter_list failed");
                printf("\n");
                return 0;
}
int parameter_declaration()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (declaration_specifiers())
	if (declarator())
                {
                printf(") => parameter_declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (declaration_specifiers())
	if (abstract_declarator()||1)
                {
                printf(") => parameter_declaration found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => parameter_declaration failed");
                printf("\n");
                return 0;
}
int identifier_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (identifier())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && identifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => identifier_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => identifier_list failed");
                printf("\n");
                return 0;
}
int initializer()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (assignment_expression())
                {
                printf(") => initializer found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_BRACE)
	if (initializer_list())
	if (COMMA)
	if (RIGHT_BRACE)
                {
                printf(") => initializer found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_BRACE)
	if (initializer_list())
	if (RIGHT_BRACE)
                {
                printf(") => initializer found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => initializer failed");
                printf("\n");
                return 0;
}
int initializer_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (initializer())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && initializer())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => initializer found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => initializer failed");
                printf("\n");
                return 0;
}
int type_name()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (specifier_qualifier_list())
	if (abstract_declarator()||1)
                {
                printf(") => type_name found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => type_name failed");
                printf("\n");
                return 0;
}
int abstract_declarator()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (pointer()||1)
	if (direct_abstract_declarator())
                {
                printf(") => abstract_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (pointer())
                {
                printf(") => abstract_declarator found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => anstract_declarator failed");
                printf("\n");
                return 0;
}
int direct_abstract_declarator()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (LEFT_PARENTHESIS && abstract_declarator() && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (LEFT_BRACKET && (constant_expression()||1) && RIGHT_BRACKET)
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (LEFT_PARENTHESIS && (parameter_type_list()||1) && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (LEFT_BRACKET && (constant_expression()||1) && RIGHT_BRACKET)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (LEFT_PARENTHESIS && (parameter_type_list()||1) && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => direct_abstract_declarator found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => direct_abstact_declarator failed");
                printf("\n");
                return 0;
}
int typedef_name()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        //if (identifier())
        if (VOID) //it should really check for identifier.
		  //since the function has not been fully implemented,
		  //we check for VOID temporarily.
                {
                printf(") => typedef_name found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => typedef_name failed");
                printf("\n");
                return 0;
}

int statement()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (labeled_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (expression_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (compound_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (selection_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (iteration_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (jump_statement())
                {
                printf(") => statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => statement failed");
                printf("\n");
                return 0;
}
int labeled_statement()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (identifier())
	if (COLON)
	if (statement())
                {
                printf(") => labeled_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (CASE)
	if (constant_expression())
	if (COLON)
	if (statement())
                {
                printf(") => labeled_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (DEFAULT)
	if (COLON)
	if (statement())
                {
                printf(") => labeled_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => labeled_statement failed");
                printf("\n");
                return 0;
}
int expression_statement()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (expression()||1)
	if (SEMICOLON)
                {
                printf(") => expression_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => expression_statement failed");
                printf("\n");
                return 0;
}

int compound_statement()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (LEFT_BRACE)
	if (declaration_list()||1)
	if (statement_list()||1)
	if (RIGHT_BRACE)
                {
                printf(") => compound_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => compund_statement failed");
                printf("\n");
                return 0;
}

int statement_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (statement())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (statement())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => statement_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => statement_list failed");
                printf("\n");
                return 0;
}

int selection_statement()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
	if (IF)
	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
	if (statement())
	if (ELSE)
	if (statement())
                {
                printf(") => selection_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (IF)
	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
	if (statement())
                {
                printf(") => selection_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (SWITCH)
	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
	if (statement())
                {
                printf(") => selection_statement found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => selection_statement failed");
                printf("\n");
                return 0;
}

int iteration_statement()
{
    long pos;
    pos = ftell(f);
		printf("(");
		printf("\n");
	if (WHILE)
	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
	if (statement())
		{
		printf(") => iteration_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (DO)
	if (statement())
	if (WHILE)
	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
	if (SEMICOLON)
		{
		printf(") => iteration_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (FOR)
	if (LEFT_PARENTHESIS)
	if (expression()||1)
	if (SEMICOLON)
	if (expression()||1)
	if (SEMICOLON)
	if (expression()||1)
	if (RIGHT_PARENTHESIS)
	if (statement())
		{
		printf(") => iteration_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

		printf(") => iteration_statement failed");
		printf("\n");
		return 0;
}
int jump_statement()
{
    long pos;
    pos = ftell(f);
		printf("(");
		printf("\n");
	if (GOTO)
	if (identifier())
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (CONTINUE)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (BREAK)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (RETURN)
	if (expression()||1)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

		printf(") => jump_statement failed");
		printf("\n");
		return 0;
}
int expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (assignment_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && assignment_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => expression failed");
                printf("\n");
                return 0;
}
int assignment_expression()
{
    long pos_s0,pos_s1,pos_s2;
    int state;
		printf("(");
		printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (unary_expression() && assignment_operator())
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (conditional_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => assignment_expression found");
		print_processed_data(pos_s0,ftell(f));
		printf("\n");
		return 1;
		}
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => assignment_expression failed");
                printf("\n");
                return 0;
}
int assignment_operator()
{
    long pos;
    pos = ftell(f);
		printf("(");
		printf("\n");
	if (EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (ASTERISK_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (FRONTSLASH_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PERCENTAGE_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PLUS_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (MINUS_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (LESSTHAN_LESSTHAN_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (GREATERTHAN_GREATERTHAN_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (AMPERSAND_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (CARAT_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PIPE_EQUAL)
		{
		printf(") => assignment_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

		printf(") =>	assignment_operator failed");
		printf("\n");
		return 0;
}
int conditional_expression()
{
    long pos_s0,pos_s1,pos_s2;
    int state;
		printf("(");
		printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (logical_OR_expression() && QUESTION_MARK && expression() && COLON)
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (logical_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => conditional_expression found");
		print_processed_data(pos_s0,ftell(f));
		printf("\n");
		return 1;
		}
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => conditional_expression failed");
                printf("\n");
                return 0;
}
int constant_expression()
{
    long pos;
    pos = ftell(f);
		printf("(");
		printf("\n");
	if (conditional_expression())
		{
		printf(") => conditional_expression found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

		printf(") => conditional_expression failed");
		printf("\n");
		return 0;
}
int logical_OR_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (logical_AND_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (PIPE_PIPE && logical_AND_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => logical_OR_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => logical_OR_expression failed");
                printf("\n");
                return 0;
}
int logical_AND_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (inclusive_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (AMPERSAND_AMPERSAND && inclusive_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => logical_AND_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => logical_AND_expression failed");
                printf("\n");
                return 0;
}
int inclusive_OR_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (exclusive_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (PIPE && exclusive_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => inclusive_OR_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => inclusive_OR_expression failed");
                printf("\n");
                return 0;
}
int exclusive_OR_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (AND_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (CARAT && AND_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => exclusive_OR_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => exclusive_OR_expression failed");
                printf("\n");
                return 0;
}
int AND_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (equality_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (AMPERSAND && equality_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => AND_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => AND_expression failed");
                printf("\n");
                return 0;
}
int equality_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (relational_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (EQUAL_EQUAL && relational_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (NOT_EQUAL && relational_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => equality_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => equality_expression failed");
                printf("\n");
                return 0;
}
int relational_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (shift_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (LESSTHAN && shift_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (GREATERTHAN && shift_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (LESSTHAN_EQUAL && shift_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (GREATERTHAN_EQUAL && shift_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => relational_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => relational_expression failed");
                printf("\n");
                return 0;
}
int shift_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (additive_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (LESSTHAN_LESSTHAN && additive_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (GREATERTHAN_GREATERTHAN && additive_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => shift_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => shift_expression failed");
                printf("\n");
                return 0;
}
int additive_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (multiplicative_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (PLUS && multiplicative_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (MINUS && multiplicative_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => additive_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => additive_expression failed");
                printf("\n");
                return 0;
}
int multiplicative_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (ASTERISK && cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (FRONT_SLASH && cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (PERCENTAGE && cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => multiplicative_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => multiplicative_expression failed");
                printf("\n");
                return 0;
}
int cast_expression()
{
    long pos_s0,pos_s1,pos_s2;
    int state;
		printf("(");
		printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (LEFT_PARENTHESIS && type_name() && RIGHT_PARENTHESIS)
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (unary_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => cast_expression found");
		print_processed_data(pos_s0,ftell(f));
		printf("\n");
		return 1;
		}
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => cast_expression failed");
                printf("\n");
                return 0;

}
int unary_expression()
{
    long pos_s0,pos_s1,pos_s2;
    int state;
		printf("(");
		printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
	if (PLUS_PLUS)
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (MINUS_MINUS)
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (SIZEOF)
	{
	goto s0;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (postfix_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (unary_operator() && cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (SIZEOF && LEFT_PARENTHESIS && type_name() && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
		printf(") => unary_expression found");
		print_processed_data(pos_s0,ftell(f));
		printf("\n");
		return 1;
		}
		//fseek(f,pos_s0,SEEK_SET);
		printf(") => unary_expression failed");
                printf("\n");
                return 0;
}
int unary_operator()
{
    long pos;
    pos = ftell(f);
		printf("(");
		printf("\n");
	if (AMPERSAND)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (ASTERISK)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PLUS)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (MINUS)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (TILDE)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (NOT)
		{
		printf(") => unary_operator found");
		print_processed_data(pos,ftell(f));
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

		printf(") => unary_operator failed");
		printf("\n");
		return 0;
}
int postfix_expression()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (primary_expression())
	{
	goto s1;
	}
	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (LEFT_BRACKET && expression() && RIGHT_BRACKET)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (LEFT_PARENTHESIS && (argument_expression_list()||1)
			     && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (DOT && identifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (ARROW && identifier())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (PLUS_PLUS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	if (MINUS_MINUS)
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => postfix_expression found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => postfix_expression failed");
                printf("\n");
                return 0;
}

int primary_expression()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (identifier())
                {
                printf(") => primary_expression found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (constant())
                {
                printf(") => primary_expression found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (string())
                {
                printf(") => primary_expression found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
                {
                printf(") => primary_expression found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => primary_expression failed");
                printf("\n");
                return 0;
}

int argument_expression_list()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (assignment_expression())
	{
	goto s1;
	}
	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
	if (COMMA && assignment_expression())
	{
	goto s1;
	}
	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		//fseek(f,pos_s1,SEEK_SET);
                printf(") => argument_expression_list found");
		print_processed_data(pos_s0,ftell(f));
                printf("\n");
                return 1;
                }
		//fseek(f,pos_s0,SEEK_SET);
                printf(") => argument_expression_list failed");
                printf("\n");
                return 0;
}

int constant()
{
    long pos;
    pos = ftell(f);
                printf("(");
                printf("\n");
        if (integer_constant())
                {
                printf(") => constant found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (character_constant())
                {
                printf(") => constant found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (floating_constant())
                {
                printf(") => constant found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (enumeration_constant())
                {
                printf(") => constant found");
		print_processed_data(pos,ftell(f));
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => constant failed");
                printf("\n");
                return 0;
}
/**************************************
End of C grammar.
**************************************/

void print_processed_data(long start_pos, long end_pos)
{
	char c;
	int flag=1; //flag is true for blank spaces, false otherwise
	fseek(f,start_pos,SEEK_SET);
	printf(" : %d : `",line_number);
	while(end_pos > start_pos)
	{
		c=getc(f);
		if (flag==1 && (c=='\n' || c==' ' || c=='\t'))
		{
			start_pos++;
			continue;
		}
		flag=0;
		putchar(c);
		start_pos++;
	}
	printf("`");
}
