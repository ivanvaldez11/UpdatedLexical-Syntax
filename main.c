#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int charClass;                 
char lexeme[100];            
char charFollowing;               
int reachLex;                
int currenttoken;                   
int followtoken;                  
FILE *in_fp;
char nextkey;                  

int definitions(char ch);       
void new_Char(void);           
void extract(void);            
void omitBlnk(void);      
int lex(void);              
void error_0(void);         

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 10
#define START 11
#define FIN 12
#define INTEGER 20
#define IDENT 21
#define AMT 22


#define ADD 30
#define SUB 31
#define MUL 32
#define DIV 33
#define MOD 34
#define OPS 40
#define CPS 41
#define OBT 42
#define CBT 43
#define COMMA 50
#define SEMICOLON 51
#define PERIOD 52
#define ONE 53
#define TWO 54
#define FOR 55 
#define EIT 56
#define LES 60
#define GTA 61
#define LTE 62
#define GTE 63
#define ETO 64
#define NET 65
#define IFSTATEMENT 70
#define CIRCUIT 80
#define NUMBERS 81

int definitions(char ch) 
{
	 switch (ch) 
   {
		 case '(':
			 new_Char();
			 followtoken = OPS;
			 break;
		 case ')':
			 new_Char();
			 followtoken = CPS;
			 break;
		 case '+':
			 new_Char();
			 followtoken = ADD;
			 break;
		 case '-':
			 new_Char();
			 followtoken = SUB;
			 break;
		 case '*':
			 new_Char();
			 followtoken = MUL;
			 break;
		 case '/':
			 new_Char();
			 followtoken = DIV;
			 break;
		 case '=':
			 new_Char();
			 followtoken = AMT;
			 break;
		 case '%':
			 new_Char();
			 followtoken = MOD;
			 break;
		 case ';':
			 new_Char();
			 followtoken = SEMICOLON;
			 break;
		 case ',':
			 new_Char();
			 followtoken = COMMA;
			 break;
		 case '{':
			 new_Char();
			 followtoken = CBT;
			 break;
		 case '}':
			 new_Char();
			 followtoken = CBT;
			 break;
		 case '.':
			 new_Char();
			 followtoken = PERIOD;
			 break;
		 case '<':
			 new_Char();
			 followtoken = LES;
			 break;
		 case '>':
			 new_Char();
			 followtoken = GTA;
			 break;
     case '@':
       new_Char();
			 followtoken = START;
			 break;
     case '^':
      new_Char();
      followtoken = FIN;
      break;
     case '#':
      new_Char();
      followtoken = NUMBERS;
      break;
    
     case '!':
      new_Char();
      followtoken = NET;
      break;
     
		 default:
			 new_Char();
			 followtoken = EOF;
			 break;
	 }
	 return followtoken;
}
void new_Char(void) 
{
	if (reachLex < 82 && reachLex != 10) 
  {
		lexeme[reachLex++] = charFollowing;
		lexeme[reachLex] = '\0';
	} 
  else
  {
    printf("Error - lexeme is too long \n");  
  }
}

void extract(void) 
{
	 if ((charFollowing = getc(in_fp)) != EOF) 
   {
		 if (isalpha(charFollowing))
     {
      charClass = LETTER;  
     } 
		 else if (isdigit(charFollowing)) 
     {
      charClass = DIGIT;  
     }
      
		 else 
     {
      charClass = UNKNOWN;  
     }
	 } 
   else
   {
     charClass = EOF;  
   } 	
}

void omitBlnk(void) 
{
	while (isspace(charFollowing))
	extract();
}

void error_0(void)
{
	printf("ERROR STOP");
  exit(0);
}

int x;
int lex(void) 
{
	reachLex = 0;
	omitBlnk();
  int x;
  int y;
	switch (charClass) 
  {
		case LETTER:
      y =1;
			new_Char();
			extract();
			while (charClass == LETTER) 
      {
        y++;
			  new_Char();
				extract();
			}
      if(y>=6 && y<=8 && lexeme[0]!='c' && lexeme[0] !='w' && lexeme[0] != 'n' )
      {
			  followtoken = IDENT;
      }
      else if(lexeme[0]=='c'&&lexeme[1]=='i'&&lexeme[2]=='r'&&lexeme[3]=='c') 
      {
        followtoken = CIRCUIT;
      }
      else if(lexeme[0]=='w'&&lexeme[1]=='h'&&lexeme[2]=='a'&&lexeme[3]=='t' ) 
      {
        followtoken = IFSTATEMENT;
      }
      else if((lexeme[1]!='i'||lexeme[2]!='r'||lexeme[3]!='c') && y>=6 && y<=8)
      {
        followtoken = IDENT;
      }  
      else
      {
        error_0();
      }
    break;
		
		case DIGIT:
			new_Char();
			extract();
			while (charClass == DIGIT) 
      {
				new_Char();
				extract();
			}
      if( charFollowing == 'v' || charFollowing == 'r' || charFollowing == 'e' )
      {
			  new_Char();
				extract();
      }
      if( charFollowing != '.')
      {
			  followtoken = INTEGER;
      } 
      else 
      {
        error_0();
		  	while (charClass == DIGIT) 
        {
			  	new_Char();
				  extract();
        }
        if( charFollowing == 'v' || charFollowing == 'r' || charFollowing == 'e' )
        {
			  	new_Char();
				  extract();
        } 
      }
		 	break;
		
		  case UNKNOWN: 
        if( charFollowing == '.')
        {
  			  new_Char();
	  		  extract();
          if(charClass == DIGIT )
          {
		  	    while (charClass == DIGIT) 
            {
			  	    new_Char();
				      extract();
			      }
            if( charFollowing == 'd' || charFollowing == 'f' )
            {
			  	    new_Char();
				      extract();
            }
			  
          }
          followtoken = PERIOD;
        } 
      else 
      {
			  definitions(charFollowing);
			  extract();
        if ( followtoken == LES && charFollowing == '=' ) 
        {
          new_Char();
          extract();
          followtoken = LES;
        }
        else if ( followtoken == GTE && charFollowing == '=' ) 
        {
          new_Char();
          extract();
          followtoken = GTE;
        }
        else if ( followtoken == AMT && charFollowing == '=' ) 
        {
          new_Char();
          extract();
          followtoken = ETO;
        }
      }
			break;
			 
		case EOF:
			 followtoken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
    case START:
      followtoken= START; 
	} 
  switch(followtoken)
  {
    case 11:
      printf("Token: START, Lexeme: %s\n", lexeme);
      break;
    case 12:
      printf("Token: FIN, Lexeme: %s\n", lexeme);
      break;
    
    case 20:
      printf("Token: INTEGER, Lexeme: %s\n", lexeme);
      break;
    case 21:
      printf("Token: IDENT, Lexeme: %s\n", lexeme);
      break;
    case 22:
      printf("Token: AMT, Lexeme: %s\n", lexeme);
      break;
    
    case 30:
      printf("Token: ADD, Lexeme: %s\n", lexeme);
      break;
    case 31:
      printf("Token: SUB, Lexeme: %s\n", lexeme);
      break;
    case 32:
      printf("Token: MUL, Lexeme: %s\n", lexeme);
      break;
    case 33:
      printf("Token: DIV, Lexeme: %s\n", lexeme);
      break;
    case 34:
      printf("Token: MOD, Lexeme: %s\n", lexeme);
      break;
    
    case 40:
      printf("Token: OPS, Lexeme: %s\n", lexeme);
      break;
    case 41:
      printf("Token: CPS, Lexeme: %s\n", lexeme);
      break;
    case 42:
      printf("Token: OBT, Lexeme: %s\n", lexeme);
      break;
    case 43:
      printf("Token: CBT, Lexeme: %s\n", lexeme);
      break;

    case 51:
      printf("Token: SEMICOLON, Lexeme: %s\n", lexeme);
      break;
    
    case 60:
      printf("Token: LES, Lexeme: %s\n", lexeme);
      break;
    case 61:
      printf("Token: GTA, Lexeme: %s\n", lexeme);
      break;
    case 62:
      printf("Token: LES, Lexeme: %s\n", lexeme);
      break;
    case 63:
      printf("Token: GTAQ, Lexeme: %s\n", lexeme);
      break;
    case 64:
      printf("Token: ETO, Lexeme: %s\n", lexeme);
      break;
    case 65:
      printf("Token: NET, Lexeme: %s\n", lexeme);
      break;
    
    case 70:
      printf("Token: IFSTATEMENT, Lexeme: %s\n", lexeme);
      break;
      
    case 80:
      printf("Token: CIRCUIT, Lexeme: %s\n", lexeme);
      break;
    case 81:
      printf("Token: NUMBERS, Lexeme: %s\n", lexeme);
      break;
  }  
	 return followtoken; 
} 