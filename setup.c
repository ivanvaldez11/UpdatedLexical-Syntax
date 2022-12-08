#include "syntax.c"

int main(void) 
{
  if ((in_fp = fopen("pass2.in", "r")) != NULL)
  {
    extract();  
	 	startup();
  }
  else if ((in_fp = fopen("pass2.in", "r")) != NULL)
  {
    extract();  
	 	startup();
  }
  else if ((in_fp = fopen("syntaxerror.in", "r")) != NULL)
  {
    extract();  
	 	startup();
  }
  else if ((in_fp = fopen("lexicalerror.in", "r")) != NULL)
  {
    extract();  
	 	startup();
  }
  else
  {
	  printf("ERROR - cannot open files \n"); 	
	}
  return 0;
} 