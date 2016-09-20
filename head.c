#include "types.h"
#include "stat.h"
#include "user.h"

/*
head -NUM FILE
prints first num lines of file
*/
char buf[512];


void head(int fd, int lineLimit)
{
  	int i, n, line;
	  i = line = 0;
  	while((n = read(fd, buf, sizeof(buf))) > 0){
    	for(i=0; i<n; i++){
    	  	if(buf[i] == '\n'){
    	  		line++;
    	  	}
          
          if(line >= lineLimit){
    	  		if(i < 512){
    	  			buf[i+1] = '\0';
    	  		}
    	  		printf(1, buf);
    	  		exit();
    	  	}
    	}
      printf(1, buf);
  	}
  	if(n < 0){
 	   printf(1, "head: read error\n");
 	   exit();
  	}
}	

int main(int argc, char *argv[])
{
	int fd, lineLimit;
	lineLimit = 0;
  	if(argc <= 1){
   	 	head(0, 10);
    	exit();
  	}else {
  		if(argc == 2){
  			lineLimit = 10;
    	}else if(argc == 3){
    		if(argv[1][0] != '-'){
    			printf(1, "2nd arg of 3 must begin with -");
    			exit();  
    		}
    		lineLimit = atoi(argv[1]+1);
    	}
    	if((fd = open(argv[argc-1], 0)) < 0){
      		printf(1, "head: cannot open %s\n", argv[1]);
     	 	exit();
     	}
    	head(fd, lineLimit);
   		close(fd);  	
   	}
	exit();
}
