/* Test program for being input to my own C compiler */
/* to check correctness of compiler */
/* Date: 01 Oct 2007 */
/* Author: Srinivas Nayak */
/* Compile using my own C compiler */

/* This code is distributed under the GPL License. */
/* For more info check: */
/* http://www.gnu.org/copyleft/gpl.html */


char stack[100];
int tos=-1;
int *f;

int identifier_flag=0;
int integer_constant_flag=0;
int floating_constant_flag=0;
int character_constant_flag=0;
int string_flag=0;

int isdigit(char);
int isletter(char);
int isspecial(char);
void push(char ch);
void pop();
void flush();
void token_error();
int get_next_token();
int check_terminal(char *terminal);

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

int identifier();
int string();
int integer_constant();
int floating_constant();
int enumeration_constant();
int character_constant();





int check_terminal(char *terminal)
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if(strcmp(terminal,stack)==0)
	{
	printf("\n-----%s-----\n\n",stack);

	    flush();
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
        }

    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }
}

int identifier()
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (identifier_flag == 1)
	{
	printf("\n-----%s-----\n\n",stack);
	    flush();
	    identifier_flag =0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    identifier_flag =0;
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
	}
    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }

}
int string()
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (string_flag == 1)
	{
	printf("\n-----%s-----\n\n",stack);
	    flush();
	    string_flag =0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    string_flag =0;
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
	}
    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }

}
int integer_constant()
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (integer_constant_flag == 1)
	{
	printf("\n-----%s-----\n\n",stack);
	    flush();
	    integer_constant_flag =0;
	    floating_constant_flag =0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    integer_constant_flag =0;
	    floating_constant_flag =0;
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
	}
    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }
}
int floating_constant()
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (floating_constant_flag == 1)
	{
	printf("\n-----%s-----\n\n",stack);
	    flush();
	    floating_constant_flag =0;
	    integer_constant_flag =0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    floating_constant_flag =0;
	    integer_constant_flag =0;
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
	}
    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }
}
int character_constant()
{
    int retval;
    long pos;
    pos = ftell(f);
    if((retval=get_next_token())!=EOF && retval == 1)
    {
	if (character_constant_flag == 1)
	{
	printf("\n-----%s-----\n\n",stack);
	    flush();
	    character_constant_flag =0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	    return 1;
	}
        else
        {
	    flush();
	    character_constant_flag =0;
	    fseek(f,pos,SEEK_SET);
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
       	    return 0;
	}
    }
    else
    {
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	return 0;
    }
}
int enumeration_constant()
{
	flush();
	return 0;
}

int main(int argc,char **argv)
{
int retval;
if(argc!=2)
  exit(0);

f=fopen(argv[1],"r");

if(f==0)
{
  printf("error");
  exit(0);
}
translation_unit();
return 0;
}
int get_next_token()
{
	char ch=0;
	int state=0;
identifier_flag=0;
integer_constant_flag=0;
floating_constant_flag=0;
character_constant_flag=0;
string_flag=0;
	s0:
	    state = 0;
	    ch=getc(f);
		if(ch==EOF)
		    return EOF;
	    if(!(ch==' ' || ch=='\n' || ch =='\t' || ch ==0))
	    push(ch);
	    if(ch==' ' || ch=='\n' || ch =='\t' || ch ==0)
	    {
		goto s0;
	    }
	    else if(isletter(ch) || ch=='_')
	    {
		goto s1;
	    }
	    else if(ch=='.')
	    {
		goto s3;
	    }
	    else if(isdigit(ch))
	    {
		goto s2;
	    }
	    else if(ch=='\'')
	    {
		goto s4;
	    }
	    else if(ch=='\"')
	    {
		goto s8;
	    }
	    else if(isspecial(ch))
	    {
		goto s10;
	    }
	    else
	    {
		goto END;
	    }
	s1:
	    state = 1;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || isdigit(ch) || ch == '_')
	    {
		goto s1;
            }
	    else
	    {
	        goto END;
	    }
	s2:
	    state = 2;
	    ch=getc(f);
	    push(ch);
	    if(ch == '.')
	    {
		goto s3;
	    }
	    else if(isdigit(ch))
	    {
		goto s2;
	    }
	    else
	    {
		goto END;
	    }
	s3:
	    state = 3;
	    ch=getc(f);
	    push(ch);
	    if(isdigit(ch))
	    {
		goto s2;
	    }
	    else
	    {
		goto END;
	    }
	s4:
	    state = 4;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || (isspecial(ch) && ch !='\'' && ch !='\\')|| isdigit(ch))
	    {
		goto s6;
	    }
	    else if(ch == '\\')
	    {
		goto s5;
	    }
	    else
	    {
		goto END;
	    }
	s5:
	    state = 5;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || isspecial(ch) || isdigit(ch))
	    {
		goto s6;
	    }
	    else
	    {
		goto END;
	    }
	s6:
	    state = 6;
	    ch=getc(f);
	    push(ch);
	    if(ch == '\'')
	    {
		goto s7;
	    }
	    else
	    {
		goto END;
	    }
	s7:
	    state = 7;
	    goto END;
	s8:
	    state = 8;
	    ch=getc(f);
	    push(ch);
	    if(isletter(ch) || (isspecial(ch) && ch != '\"') || isdigit(ch))
	    {
		goto s8;
	    }
	    else if(ch == '\"')
	    {
		goto s9;
	    }
	    else
	    {
		goto END;
	    }
	s9:
	    state = 9;
	    goto END;
	s10:
	    state = 10;
		fseek(f,-1,SEEK_CUR);
		pop();
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
		    goto END;
	    s11:
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
		    goto END;
	    s12:
	        state = 12;
		    goto END;
	    s13:
	        state = 13;
		    goto END;
	    s14:
	        state = 14;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s15:
	        state = 15;
		    goto END;
	    s16:
	        state = 16;
		    goto END;
	    s17:
	        state = 17;
	        ch=getc(f);
	        push(ch);
		if(ch=='+')
		    goto s18;
		else if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s18:
	        state = 18;
		    goto END;
	    s19:
	        state = 19;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s20:
	        state = 20;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s21:
	        state = 21;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s22:
	        state = 22;
	        ch=getc(f);
	        push(ch);
		if(ch=='<')
		    goto s23;
		else if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s23:
	        state = 23;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s24:
	        state = 24;
	        ch=getc(f);
	        push(ch);
		if(ch=='>')
		    goto s25;
		else if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s25:
	        state = 25;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s26:
	        state = 26;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s27:
	        state = 27;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else if(ch=='&')
		    goto s28;
		else
		    goto END;
	    s28:
	        state = 28;
		    goto END;
	    s29:
	        state = 29;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else
		    goto END;
	    s30:
	        state = 30;
	        ch=getc(f);
	        push(ch);
		if(ch=='=')
		    goto s15;
		else if(ch=='|')
		    goto s31;
		else
		    goto END;
	    s31:
	        state = 31;
		    goto END;
	    s32:
	        state = 32;
		    goto END;
	END:
	    if(!(state==7
		|| state==9
		|| state==10
		|| state==12
		|| state==13
		|| state==15
		|| state==16
		|| state==18
		|| state==28
		|| state==31
		|| state==32
		))
	    {
		fseek(f,-1,SEEK_CUR);
		pop();
	    }
	    if(state==1
		|| state==2
		|| state==7
		|| state==9
		|| state==10
		|| (state>=11 && state<=32)
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
			{
			identifier_flag=1;
			}
			break;
		    case 2:
			{
			integer_constant_flag=1;
			floating_constant_flag=1;
			}
			break;
		    case 7:
			{
			character_constant_flag=1;
			}
			break;
		    case 9:
			{
			string_flag=1;
			}
			break;
		    case 10:
			break;
		    default:
			break;
		}
	    }
	    else
	    {
		return 0;
	    }
return 1;
}
void token_error()
{
	printf("%25s","error at : ");
	flush();
	printf("\n");
}
int isdigit(char ch)
{
	if(ch >= 48 && ch <= 57)
	    return 1;
	else
	    return 0;
}
int isletter (char ch)
{
	if((ch >= 'A' && ch <=  'Z') || (ch >= 'a' && ch <= 'z') )
	    return 1;
	else
	    return 0;
}
int isspecial (char ch)
{
	if(!(isdigit(ch) || isletter(ch)))
	    return 1;
	else
	    return 0;
}
void push(char ch)
{
	if(tos==98)
	   exit(0);
	tos++;
	stack[tos]=ch;
	stack[tos+1]='\0';
}
void pop()
{
	if(tos==-1)
	   exit(0);
	tos--;
	stack[tos+1]='\0';
}
void flush()
{
	tos=-1;
	stack[tos+1]='\0';
}


int translation_unit()
{
    long pos_s0,pos_s1;
    int state;
                printf("(");
                printf("\n");
s0:
	state = 0;
	pos_s0 = ftell(f);
        if (external_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s0,SEEK_SET);
	goto END;
s1:
	state = 1;
	pos_s1 = ftell(f);
        if (external_declaration())
	{
	goto s1;
	}

	fseek(f,pos_s1,SEEK_SET);
	goto END;
END:
	if (state == 1)
		{
		fseek(f,pos_s1,SEEK_SET);
                printf(") => translation_unit found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
                printf(") => translation_unit failed");
                printf("\n");
                return 0;
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (function_definition())
                {
                printf(") => external_declaration found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => declaration_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => declaration_specifiers found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (REGISTER)
                {
                printf(") => storage_class_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (STATIC)
                {
                printf(") => storage_class_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (EXTERN)
                {
                printf(") => storage_class_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (TYPEDEF)
                {
                printf(") => storage_class_specifier found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (CHAR)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (SHORT)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (INT)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LONG)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (FLOAT)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (DOUBLE)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (SIGNED)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (UNSIGNED)
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (struct_or_union_specifier())
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (enum_specifier())
                {
                printf(") => type_specifier found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (typedef_name())
                {
                printf(") => type_specifier found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (VOLATILE)
                {
                printf(") => type_qualifier found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (struct_or_union())
	if (identifier())
                {
                printf(") => struct_or_union_specifier found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (UNION)
                {
                printf(") => struct_or_union found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => struct_declaration_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => init_declarator_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (declarator())
                {
                printf(") => init_declarator found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => specifier_qualifier_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => struct_declaratoe_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (declarator())
                {
                printf(") => struct_declarator found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (ENUM)
	if (identifier())
                {
                printf(") => enum_specifier found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => enumerator_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (identifier())
                {
                printf(") => identifier found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => direct_declarator found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => pointer found");
		printf("\n");
		return 1;
		}
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => type_qualifier found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (parameter_list())
                {
                printf(") => parameter_type_list found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => parameter_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (declaration_specifiers())
	if (abstract_declarator()||1)
                {
                printf(") => parameter_declaration found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => identifier_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf(") => initializer_list found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_BRACE)
	if (initializer_list())
	if (COMMA)
	if (RIGHT_BRACE)
                {
                printf(") => initializer_list found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_BRACE)
	if (initializer_list())
	if (RIGHT_BRACE)
                {
                printf(") => initializer_list found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => initializer_list failed");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => initializer found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

        if (pointer())
                {
                printf(") => abstract_declarator found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => direct_abstract_declarator found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
        if (VOID)
                {
                printf(") => typedef_name found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (expression_statement())
                {
                printf(") => statement found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (compound_statement())
                {
                printf(") => statement found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (selection_statement())
                {
                printf(") => statement found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (iteration_statement())
                {
                printf(") => statement found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (jump_statement())
                {
                printf(") => statement found");
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (DEFAULT)
	if (COLON)
	if (statement())
                {
                printf(") => labeled_statement found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => statement_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (CONTINUE)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (BREAK)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (RETURN)
	if (expression()||1)
	if (SEMICOLON)
		{
		printf(") => jump_statement found");
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
	goto s2;
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
s2:
	state = 2;
	pos_s2 = ftell(f);
	if (conditional_expression())
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	goto END;

END:
	if (state == 1)
		{
		fseek(f,pos_s1,SEEK_SET);
		printf(") => assignment_expression found");
		printf("\n");
		return 1;
		}
		fseek(f,pos_s0,SEEK_SET);
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
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (ASTERISK_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (FRONTSLASH_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PERCENTAGE_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PLUS_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (MINUS_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (LESSTHAN_LESSTHAN_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (GREATERTHAN_GREATERTHAN_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (AMPERSAND_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (CARAT_EQUAL)
		{
		printf(") => assignment_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PIPE_EQUAL)
		{
		printf(") => assignment_operator found");
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
	goto s2;
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
s2:
	state = 2;
	pos_s2 = ftell(f);
	if (logical_OR_expression())
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	goto END;

END:
	if (state == 1)
		{
		fseek(f,pos_s1,SEEK_SET);
		printf(") => conditional_expression found");
		printf("\n");
		return 1;
		}
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => logical_OR_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => logical_AND_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => inclusive_OR_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => exclusive_OR_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => AND_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => equality_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => relational_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => shift_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => additive_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
		fseek(f,pos_s1,SEEK_SET);
		printf(") => multiplicative_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
	goto s2;
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
s2:
	state = 2;
	pos_s2 = ftell(f);
	if (unary_expression())
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	goto END;

END:
	if (state == 1)
		{
		fseek(f,pos_s1,SEEK_SET);
		printf(") => cast_expression found");
		printf("\n");
		return 1;
		}
		fseek(f,pos_s0,SEEK_SET);
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
	goto s2;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (MINUS_MINUS)
	{
	goto s2;
	}

	fseek(f,pos_s0,SEEK_SET);
	if (SIZEOF)
	{
	goto s2;
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
s2:
	state = 2;
	pos_s2 = ftell(f);
	if (postfix_expression())
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	if (unary_operator() && cast_expression())
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	if (SIZEOF && LEFT_PARENTHESIS && type_name() && RIGHT_PARENTHESIS)
	{
	goto s1;
	}

	fseek(f,pos_s2,SEEK_SET);
	goto END;

END:
	if (state == 1)
		{
		fseek(f,pos_s1,SEEK_SET);
		printf(") => unary_expression found");
		printf("\n");
		return 1;
		}
		fseek(f,pos_s0,SEEK_SET);
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
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (ASTERISK)
		{
		printf(") => unary_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (PLUS)
		{
		printf(") => unary_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (MINUS)
		{
		printf(") => unary_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (TILDE)
		{
		printf(") => unary_operator found");
		printf("\n");
		return 1;
		}
	    fseek(f,pos,SEEK_SET);

	if (NOT)
		{
		printf(") => unary_operator found");
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
	if (LEFT_PARENTHESIS && (argument_expression_list()||1) && RIGHT_PARENTHESIS)
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => postfix_expression found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (constant())
                {
                printf(") => primary_expression found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (string())
                {
                printf(") => primary_expression found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (LEFT_PARENTHESIS)
	if (expression())
	if (RIGHT_PARENTHESIS)
                {
                printf(") => primary_expression found");
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
		fseek(f,pos_s1,SEEK_SET);
                printf(") => argument_expression_list found");
                printf("\n");
                return 1;
                }
		fseek(f,pos_s0,SEEK_SET);
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
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (character_constant())
                {
                printf(") => constant found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (floating_constant())
                {
                printf(") => constant found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

	if (enumeration_constant())
                {
                printf(") => constant found");
                printf("\n");
                return 1;
                }
	    fseek(f,pos,SEEK_SET);

                printf(") => constant failed");
                printf("\n");
                return 0;
abcd=0;
}
static const struct {
    int y;
    int x;
} offsets[] = {
    { 2, 1 },
    { 1, 2 },
    { -1, 2 },
    { -2, 1 },
    { -2, -1 },
    { -1, -2 },
    { 1, -2 },
    { 2, -1 },
};


static void
init_program(void)
{
    setlocale(LC_ALL, "");

    srand((unsigned) getpid());
    initscr();
    cbreak();
    noecho();
    boardwin = newwin(8 * 2 + 1, 8 * 4 + 1, 2, 0);
    helpwin = newwin(0, 0, 2, 35);
    msgwin = newwin(1, 35 - 1, 21, 0);
    scrollok(msgwin, TRUE);
    keypad(boardwin, TRUE);

    if (has_colors()) {
        int bg = COLOR_BLACK;

        start_color();





        (void) init_pair(1, COLOR_CYAN, bg);
        (void) init_pair(2, COLOR_RED, bg);
        (void) init_pair(3, COLOR_GREEN, bg);

        trail |= COLOR_PAIR(1);
        plus |= COLOR_PAIR(2);
        minus |= COLOR_PAIR(3);
    }




    oldch = minus;
}

static void
help1(void)

{
    (void) waddstr(helpwin, "Knight's move is a solitaire puzzle.  Your\n");
    (void) waddstr(helpwin, "objective is to visit each square of the  \n");
    (void) waddstr(helpwin, "chessboard exactly once by making knight's\n");
    (void) waddstr(helpwin, "moves (one square right or left followed  \n");
    (void) waddstr(helpwin, "by two squares up or down, or two squares \n");
    (void) waddstr(helpwin, "right or left followed by one square up or\n");
    (void) waddstr(helpwin, "down).  You may start anywhere.\n\n");

    (void) waddstr(helpwin, "Use arrow keys to move the cursor around.\n");
    (void) waddstr(helpwin, "When you want to move your knight to the \n");
    (void) waddstr(helpwin, "cursor location, press <space> or Enter.\n");
    (void) waddstr(helpwin, "Illegal moves will be rejected with an  \n");
    (void) waddstr(helpwin, "audible beep.\n\n");
    (void) waddstr(helpwin, "The program will detect if you solve the\n");
    (void) waddstr(helpwin, "puzzle; also inform you when you run out\n");
    (void) waddstr(helpwin, "of legal moves.\n\n");

    (void) mvwaddstr(helpwin, 21 - 2, 0,
                     "Press `?' to go to keystroke help.");
}

static void
help2(void)

{
    (void) waddstr(helpwin, "Possible moves are shown with `-'.\n\n");

    (void) waddstr(helpwin, "You can move around with the arrow keys or\n");
    (void) waddstr(helpwin, "with the rogue/hack movement keys.  Other\n");
    (void) waddstr(helpwin, "commands allow you to undo moves or redraw.\n");
    (void) waddstr(helpwin, "Your mouse may work; try left-button to\n");
    (void) waddstr(helpwin, "move to the square under the pointer.\n\n");

    (void) waddstr(helpwin, "x,q -- exit             y k u    7 8 9\n");
    (void) waddstr(helpwin, "r -- redraw screen       \\|/      \\|/ \n");
    (void) waddstr(helpwin, "bksp -- undo move       h-+-l    4-+-6\n");
    (void) waddstr(helpwin, "a -- autojump            /|\\      /|\\ \n");
    (void) waddstr(helpwin, "                        b j n    1 2 3\n");

    (void) waddstr(helpwin, "\nYou can place your knight on the selected\n");
    (void) waddstr(helpwin, "square with spacebar, Enter, or the keypad\n");
    (void) waddstr(helpwin, "center key.  Use F/B to review the path.\n");

    (void) mvwaddstr(helpwin, 21 - 2, 0,
                     "Press `?' to go to game explanation");
}

static void
show_help(int * keyhelp)
{
    werase(helpwin);
    if (*keyhelp) {
        help1();
        *keyhelp = FALSE;
    } else {
        help2();
        *keyhelp = TRUE;
    }
    wrefresh(helpwin);
}

static int
chksqr(int r1, int c1)
{
    if ((r1 < 0) || (r1 > 8 - 1))
        return (FALSE);
    if ((c1 < 0) || (c1 > 8 - 1))
        return (FALSE);
    return ((!board[r1][c1]) ? TRUE : FALSE);
}

static int
chkmoves(int rw, int col)

{
}

static void
dosquares(void)
{
    int i, j;

    mvaddstr(0, 20, "KNIGHT'S MOVE -- a logical solitaire");

    move(2, 0);
    waddch(boardwin, ACS_ULCORNER);
    for (j = 0; j < 7; j++) {
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_TTEE);
    }
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_URCORNER);

    for (i = 1; i < 8; i++) {
        move(2 + i * 2 - 1, 0);
        waddch(boardwin, ACS_VLINE);
        for (j = 0; j < 8; j++) {
            waddch(boardwin, ' ');
            waddch(boardwin, ' ');
            waddch(boardwin, ' ');
            waddch(boardwin, ACS_VLINE);
        }
        move(2 + i * 2, 0);
        waddch(boardwin, ACS_LTEE);
        for (j = 0; j < 8 - 1; j++) {
            waddch(boardwin, ACS_HLINE);
            waddch(boardwin, ACS_HLINE);
            waddch(boardwin, ACS_HLINE);
            waddch(boardwin, ACS_PLUS);
        }
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_RTEE);
    }

    move(2 + i * 2 - 1, 0);
    waddch(boardwin, ACS_VLINE);
    for (j = 0; j < 8; j++) {
        waddch(boardwin, ' ');
        waddch(boardwin, ' ');
        waddch(boardwin, ' ');
        waddch(boardwin, ACS_VLINE);
    }

    move(2 + i * 2, 0);
    waddch(boardwin, ACS_LLCORNER);
    for (j = 0; j < 8 - 1; j++) {
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_HLINE);
        waddch(boardwin, ACS_BTEE);
    }
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_HLINE);
    waddch(boardwin, ACS_LRCORNER);
}

static void
mark_possibles(int prow, int pcol, int mark)
{
    unsigned n;

    for (n = 0; n < SIZEOF(offsets); n++) {
        if (chksqr(prow + offsets[n], pcol + offsets[n])) {
            wmove(boardwin, (1 + 2 * (prow + offsets[n])), (2 + 4 * (pcol + offsets[n])));
            waddch(boardwin, mark);
        }
    }
}

static void
find_next_move(int *y, int *x)
{
    unsigned j, k;
    int found = -1;
    int first = -1;
    int next = 0;
    int oldy, oldx;
    int newy, newx;

    if (movecount > 1) {
        oldy = history[movecount - 1];
        oldx = history[movecount - 1];
        for (j = 0; j < SIZEOF(offsets) * 2; j++) {
            k = j % SIZEOF(offsets);
            newy = oldy + offsets[k].y;
            newx = oldx + offsets[k].x;
            if (chksqr(newy, newx)) {
                if (first < 0)
                    first = k;
                if (newy == *y
                    && newx == *x) {
                    found = k;
                } else if (found >= 0) {
                    next = k;
                    break;
                }
            }
        }
        if (found < 0)
            next = first;
        if (next >= 0) {
            *y = oldy + offsets[next].y;
            *x = oldx + offsets[next].x;
        }
    } else {
        beep();
    }
}

static void
unmarkcell(int row, int column)
{
    wmove(boardwin, (1 + 2 * (row)), (2 + 4 * (column)));
    waddch(boardwin, '\b');
    waddch(boardwin, ' ');
    waddch(boardwin, minus);
    waddch(boardwin, ' ');
}

static void
markcell(int tchar, int row, int column)
{
    wmove(boardwin, (1 + 2 * (row)), (2 + 4 * (column)));
    waddch(boardwin, '\b');
    waddch(boardwin, tchar);
    waddch(boardwin, tchar);
    waddch(boardwin, tchar);
}

static void
drawmove(int tchar, int oldy, int oldx, int row, int column)

{
    if (movecount <= 1) {
        int i, j;

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (movecount == 0) {
                    unmarkcell(i, j);
                } else {
                    wmove(boardwin, (1 + 2 * (i)), (2 + 4 * (j)));
                    if (winch(boardwin) == minus)
                        waddch(boardwin, movecount ? ' ' : minus);
                }
            }
        }
    } else {
        markcell(tchar, oldy, oldx);
        mark_possibles(oldy, oldx, ' ');
    }

    if (row != -1 && column != -1) {
        markcell(trail, row, column);
        mark_possibles(row, column, minus);
        board[row][column] = TRUE;
    }

    wprintw(msgwin, "\nMove %d", movecount);
    if (trialcount != movecount)
        wprintw(msgwin, " (%d tries)", trialcount);
    wclrtoeol(msgwin);
}

static int
iabs(int num)
{
    if (num < 0)
        return (-num);
    else
        return (num);
}

evalmove(int row, int column)

{
    if (movecount == 1)
        return (TRUE);
    else if (board[row][column] == TRUE) {
        waddstr(msgwin, "\nYou've already been there.");
        return (FALSE);
    } else {
        int rdif = iabs(row - history[movecount - 1].y);
        int cdif = iabs(column - history[movecount - 1].x);

        if (!((rdif == 1) && (cdif == 2)) && !((rdif == 2) && (cdif == 1))) {
            waddstr(msgwin, "\nThat's not a legal knight's move.");
            return (FALSE);
        }
    }

    return (TRUE);
}

static int
completed(void)
{
    int i, j, count = 0;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (board[i][j] != 0)
                count += 1;
    return (count == (8 * 8) ? -1 : count);
}

static void
no_previous_move(void)
{
    waddstr(msgwin, "\nNo previous move.");
    beep();
}

static void
play(void)

{
    int i, j, count;
    int lastcol = 0;
    int lastrow = 0;
    int ny = 0, nx = 0;
    int review = 0;
    int rw = 0, col = 0;

    do {

        werase(boardwin);
        werase(helpwin);
        werase(msgwin);
        dosquares();
        help1();
        wnoutrefresh(stdscr);
        wnoutrefresh(helpwin);
        wnoutrefresh(msgwin);
        wnoutrefresh(boardwin);
        doupdate();

        movecount = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                board[i][j] = FALSE;
                unmarkcell(i, j);
            }
        }
        memset(history, 0, sizeof(history));
        history[0].y = history[0].x = -1;
        history[1].y = history[1].x = -1;
        lastrow = lastcol = -2;
        movecount = 1;
        trialcount = 1;
        keyhelp = FALSE;
        show_help(&keyhelp);

        for (;;) {
            if (rw != lastrow || col != lastcol) {
                if (lastrow >= 0 && lastcol >= 0) {
                    wmove(boardwin, (1 + 2 * (lastrow)), (2 + 4 * (lastcol)));
                    if (board[lastrow][lastcol])
                        waddch(boardwin, trail);
                    else
                        waddch(boardwin, oldch);
                }

                wmove(boardwin, (1 + 2 * (rw)), (2 + 4 * (col)));
                oldch = winch(boardwin);

                lastrow = rw;
                lastcol = col;
            }
            wmove(boardwin, (1 + 2 * (rw)), (2 + 4 * (col)));
            waddch(boardwin, plus);
            wmove(boardwin, (1 + 2 * (rw)), (2 + 4 * (col)));

            wrefresh(msgwin);

            switch (wgetch(boardwin)) {
            case 'k':
            case '8':
            case KEY_UP:
                ny = rw + 8 - 1;
                nx = col;
                break;
            case 'j':
            case '2':
            case KEY_DOWN:
                ny = rw + 1;
                nx = col;
                break;
            case 'h':
            case '4':
            case KEY_LEFT:
                ny = rw;
                nx = col + 8 - 1;
                break;
            case 'l':
            case '6':
            case KEY_RIGHT:
                ny = rw;
                nx = col + 1;
                break;
            case 'y':
            case '7':
            case KEY_A1:
                ny = rw + 8 - 1;
                nx = col + 8 - 1;
                break;
            case 'b':
            case '1':
            case KEY_C1:
                ny = rw + 1;
                nx = col + 8 - 1;
                break;
            case 'u':
            case '9':
            case KEY_A3:
                ny = rw + 8 - 1;
                nx = col + 1;
                break;
            case 'n':
            case '3':
            case KEY_C3:
                ny = rw + 1;
                nx = col + 1;
                break;
            case KEY_B2:
            case '\n':
            case ' ':
                review = 0;
                if (evalmove(rw, col)) {
                    drawmove(trail,
                             history[movecount - 1].y,
                             history[movecount - 1].x,
                             rw, col);
                    history[movecount].y = rw;
                    history[movecount].x = col;
                    movecount++;
                    trialcount++;

                    if (!chkmoves(rw, col)) {
                        if (completed() < 0) {
                            waddstr(msgwin, "\nYou won.");
                        } else {
                            waddstr(msgwin,
                                    "\nNo further moves are possible.");
                        }
                    }
                } else {
                    beep();
                }
                break;

            case KEY_UNDO:
            case KEY_BACKSPACE:
            case '\b':
                review = 0;
                if (movecount <= 0) {
                    no_previous_move();
                } else if (movecount <= 1) {
                    ny = history[movecount].y;
                    nx = history[movecount].x;
                    if (nx < 0 || ny < 0) {
                        ny = lastrow;
                        nx = lastcol;
                    }
                    movecount = 0;
                    board[ny][nx] = FALSE;
                    oldch = minus;
                    drawmove(' ', ny, nx, -1, -1);
                    movecount = 1;
                    trialcount = 1;
                    no_previous_move();
                } else {
                    int oldy = history[movecount - 1].y;
                    int oldx = history[movecount - 1].x;

                    if (!board[rw][col]) {
                        wmove(boardwin, (1 + 2 * (rw)), (2 + 4 * (col)));
                        waddch(boardwin, ' ');
                    }

                    board[oldy][oldx] = FALSE;
                    --movecount;
                    ny = history[movecount - 1].y;
                    nx = history[movecount - 1].x;
                    if (nx < 0 || ny < 0) {
                        ny = oldy;
                        nx = oldx;
                    }
                    drawmove(' ', oldy, oldx, ny, nx);


                    wmove(boardwin, (1 + 2 * (lastrow)), (2 + 4 * (lastcol)));
                    oldch = winch(boardwin);
                }
                break;

            case 'a':
                nx = col;
                ny = rw;
                find_next_move(&ny, &nx);
                break;

            case 'F':
                if (review > 0) {
                    review--;
                    ny = history[movecount - review - 1].y;
                    nx = history[movecount - review - 1].x;
                } else {
                    beep();
                }
                break;

            case 'B':
                if (review < movecount - 2) {
                    review++;
                    ny = history[movecount - review - 1].y;
                    nx = history[movecount - review - 1].x;
                } else {
                    beep();
                }
                break;

            case KEY_REDO:
            case '\f':
            case 'r':
                clearok(curscr, TRUE);
                wnoutrefresh(stdscr);
                wnoutrefresh(boardwin);
                wnoutrefresh(msgwin);
                wnoutrefresh(helpwin);
                doupdate();
                break;

            case 'q':
            case 'x':
                goto dropout;

            case '?':
                show_help(&keyhelp);
                break;

            default:
                beep();
                break;
            }

            col = nx % 8;
            rw = ny % 8;
        }

      dropout:
        if ((count = completed()) < 0)
            wprintw(msgwin, "\nYou won.  Care to try again? ");
        else
            wprintw(msgwin, "\n%d squares filled.  Try again? ", count);
        wclrtoeol(msgwin);
    } while
        (tolower(wgetch(msgwin)) == 'y');
}

int
main(int argc, char *argv[], ...)
{
    init_program();

    play();

    endwin();
    ExitProgram(EXIT_SUCCESS);
}
