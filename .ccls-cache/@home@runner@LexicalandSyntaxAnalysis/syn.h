#include "lex.h"

void startup(void);        
void express(void);
void terminol(void);
void factor(void);
void ifsmt(void);
void statement(void);
void loop(void);
void booLean(void);
void equal_to(void);    
void comp(void);
void mod(void);


//void statement(void);
void startup(void) //<startup> -> Beginner <statement> {<statement>} End 
{ 
  printf("Enter <Beginner>\n"); //glossary(char ch)
  lex(); //Parse term 1
  if(followTK == Beginner)
  {
    lex();
	  statement();
    while(followTK==S_COLON)
    {
      lex();
    }
    if(followTK == Finisher)
    { 
      printf("pass");   //endpoint
    } 
    while(followTK==S_COLON)
    {
      lex();
    }
    while(followTK!= Finisher && followTK!=EOF) //check for possible file repeat for processing
    { 
      statement();
    }
    if(followTK==Finisher)
    {
      printf("pass\n"); //pass
    }
    else
    {  
      error_0();
    }
  }  
  else
  {
    error_0();
  }
  printf("Exit <startup>\n");
}
  
void express(void)  //<express> ->  <terminol> {(+ | *) <terminol>} 
{ 
	printf("Enter <express>\n"); // Parse the first term @ lex();
	terminol();
	while (followTK == ADDITION || followTK == MULTIPLY) // Parse next term while next token is '+' or '*'
  {
    lex();
		terminol();
	}
	printf("Exit <express>\n");
}

void terminol(void) // <terminol> -> <comp> {(- | / ) <comp>}
{
	printf("Enter <term>\n"); 
	comp(); // Parse the first comp 
	while (followTK == SUBTRACT || followTK == DIVIDE ) //parse next factor while next token is '-' or '/'
  {
    lex();
		comp();
	}
	printf("Exit <term>\n");
}

void comp(void) // <comp>-> <equal_to> {(<|>|<=|>=|==) <equal_to>}
{
printf("Enter <comp>\n");
	
	 equal_to(); //Parse first factor
	 while (followTK == LARGER|| followTK == SMALLERQ || followTK == LARGERQ || followTK == SMALLER || followTK==EQUAL_V) //Parse next factor upon '*' or '/' and repeat
   {
     lex();
		 equal_to();
	 }
	 printf("Exit <comp>\n");  
}

void equal_to(void) //<equal_to> -> <mod>{(=|!=)<mod> }
{ 
printf("Enter <equal_to>\n"); 
	mod(); // Parse first factor
	while (followTK == ASSGNMNT|| followTK == NOTEQUAL)  // Parse next factor upon '=' or '!=' 
  {
    lex();
	  mod();
	}
	printf("Exit <equality>\n");  
}

void mod(void) //<mod>-> <factor> {(%|;)<factor>}
{ 
printf("Enter <mod>\n");
	 factor(); // Parse first factor
	 while (followTK == MODULUS  || followTK== S_COLON)  // Parse next modulus while '%'
   {
		 factor();
	 }
	 printf("Exit <mod>\n");  
}




void factor(void) // <factor> -> id | int_constant | num identify | ( <express> ) | s_colon
{
	 printf("Enter <factor>\n");	// Determine Right Hand Side

  if(followTK==NUMERICS) //lex();
  {
    lex();
    if(followTK==IDENTIFY)
    {
      lex();
       if(followTK==S_COLON)
       {
        lex(); 
       }
       else
       {
         error_0();
       }
    }
    else
    {
      error_0();
    }
  }
	else if (followTK == IDENTIFY || followTK == INTEGER || followTK==S_COLON )
  {
		lex(); // extract next token
  }
	else  if (followTK == STARTPAR) //Call lex for left paren, express, and right paren if Right Hand Side is ( <express> )
  {
    lex();
		express();
		if (followTK == ENDPAR)
    {
      lex();  
    }
		else
    {
		 	error_0();
		} 
  }
	else            // Not id, int lit, nor right paren
  {
		error_0();
	}
	printf("Exit <factor>\n");  
}

void ifsmt(void) //<ifsmt>-> con'('<booLean>')''{'<statement'}' {<statement} 
{ 
   printf("Enter <ifsmt>\n");
	if (followTK == STARTPAR ) 
  {
    lex();     //lex();
    booLean();
    if(followTK==ENDPAR)
    {
      lex();
      if(followTK==STARTBRK)
      {
        lex();
        statement();
        if(followTK==ENDBRK)
        {
          lex();
          if(followTK!= Finisher && followTK!=EOF) 
          {
            statement();
          }
        }
        else
        {
          error_0();
        }
      }
      else
      {
        error_0();
      }
    }
    else 
    {
      error_0();
    }
  }
  else 
  {
    error_0();
  } 
} 

void statement(void) // <statement>-> <ifsmt> | <loop> | <express>   
{
     printf("Enter <statement>\n");
    // lex();
    if(followTK==IF_STMT)
    {
      lex();
      ifsmt();
    }
    else if(followTK == CIRCUIT)
    {
      lex();
      loop();
    }
   else
    {
     express();
   }
     printf("Exit <statement>\n");
}

void loop(void) //  <loop> -> loop(<booLean>) '{' <statement> '}' {<statement>}  
{
  printf("Enter <loop>\n");  
  if(followTK==STARTPAR) //lex();
  {
    lex();
    booLean();
    if(followTK == ENDPAR)
    {
      lex();
      if(followTK==STARTBRK)
      {
        lex();
        statement();
        if(followTK == ENDBRK)
        {
          lex();
          if(followTK!= Finisher && followTK!=EOF) 
          {
            statement();
          }
        }
        else
        {
          error_0();
        }
      }
    }
  }
  else
  {
    error_0();
  }
} 


void booLean(void) // <booLean>-> identifer (<|>|<=|>=|==|!) INTEGER
{
   printf("Enter <booLean>\n");
  if(followTK==IDENTIFY) //lex();
  {
    lex();
    if(followTK == SMALLER ||followTK==LARGER || followTK == SMALLERQ || followTK == LARGERQ || followTK==NOTEQUAL||followTK==EQUAL_V )
    {
      lex();
      if(followTK==INTEGER)
      {
        lex();
      }
      else 
      {
        error_0();
      }
    }
    else 
    {
      error_0();
    }
  }
  else
  {
    error_0();
  }
  printf("exit <booLean>\n");
} 