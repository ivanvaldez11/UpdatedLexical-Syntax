#include "main.c"

void startup(void);        
void express(void);
void terminol(void);
void factor(void);
void ifstatement(void);
void statement(void);
void loop(void);
void booLean(void);
void equal(void);    
void complic(void);
void module(void);

void startup(void) 
{ 
  printf("Enter <Start>\n"); 
  lex(); 
  if(followtoken == START)
  {
    lex();
	  statement();
    while(followtoken==SEMICOLON)
    {
      lex();
    }
    if(followtoken == FIN)
    { 
      printf("pass");   
    } 
    while(followtoken==SEMICOLON)
    {
      lex();
    }
    while(followtoken!= FIN && followtoken!=EOF) 
    { 
      statement();
    }
    if(followtoken==FIN)
    {
      printf("pass\n");
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
  
void express(void)  
{ 
	printf("Enter <express>\n"); 
	terminol();
	while (followtoken == ADD || followtoken == MUL) 
  {
    lex();
		terminol();
	}
	printf("Exit <express>\n");
}

void terminol(void) 
{
	printf("Enter <terminol>\n"); 
	complic(); 
	while (followtoken == SUB || followtoken == DIV ) 
  {
    lex();
		complic();
	}
	printf("Exit <terminol>\n");
}

void complic(void) 
{
printf("Enter <complic>\n");
	
	 equal();
	 while (followtoken == GTA|| followtoken == LES || followtoken == GTA || followtoken == LES || followtoken==ETO) 
   {
     lex();
		 equal();
	 }
	 printf("Exit <complic>\n");  
}

void equal(void) 
{ 
printf("Enter <equal>\n"); 
	module(); 
	while (followtoken == AMT|| followtoken == NET)  
  {
    lex();
	  module();
	}
	printf("Exit <equal>\n");  
}

void module(void) 
{ 
printf("Enter <module>\n");
	 factor(); 
	 while (followtoken == MOD  || followtoken== SEMICOLON)  
   {
		 factor();
	 }
	 printf("Exit <module>\n");  
}




void factor(void) 
{
	 printf("Enter <factor>\n");	

  if(followtoken==NUMBERS) 
  {
    lex();
    if(followtoken==IDENT)
    {
      lex();
       if(followtoken==SEMICOLON)
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
	else if (followtoken == IDENT || followtoken == INTEGER || followtoken==SEMICOLON )
  {
		lex(); 
  }
	else  if (followtoken == OPS) 
  {
    lex();
		express();
		if (followtoken == CPS)
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
	printf("Exit <factor>\n");  
}

void ifstatement(void) 
{ 
   printf("Enter <ifstatment>\n");
	if (followtoken == OPS ) 
  {
    lex();     
    booLean();
    if(followtoken==CPS)
    {
      lex();
      if(followtoken==OBT)
      {
        lex();
        statement();
        if(followtoken==CBT)
        {
          lex();
          if(followtoken!= FIN && followtoken!=EOF) 
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

void statement(void) 
{
     printf("Enter <statement>\n");
    if(followtoken==IFSTATEMENT)
    {
      lex();
      ifstatement();
    }
    else if(followtoken == CIRCUIT)
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

void loop(void) 
{
  printf("Enter <loop>\n");  
  if(followtoken==OPS) 
  {
    lex();
    booLean();
    if(followtoken == CPS)
    {
      lex();
      if(followtoken==OBT)
      {
        lex();
        statement();
        if(followtoken == CBT)
        {
          lex();
          if(followtoken!= FIN && followtoken!=EOF) 
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
void booLean(void) 
{
   printf("Enter <booLean>\n");
  if(followtoken==IDENT) 
  {
    lex();
    if(followtoken == LES ||followtoken==GTA || followtoken == LES || followtoken == GTA || followtoken==NET||followtoken==ETO )
    {
      lex();
      if(followtoken==INTEGER)
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