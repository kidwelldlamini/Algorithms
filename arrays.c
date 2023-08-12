#include <stdio.h> 
#include <string.h>
int main()//fonction principale
{

char  name[10] = "letho";
int longeur=0;

printf("%s\n",name);
scanf("%s",name);

longeur = strlen(name);
for (int i=0;i<longeur;i++) {
    printf("%c",*(name+i));
}
return 0;
}