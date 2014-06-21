#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* 
   count -> count to allocate dynamic array
   line -> count of line
   initial -> 
   final ->
   ln[] -> int array to store line numbers arr[]
   ln1[] -> int array to store line numbers in arr1[]
	
   curr_pos -> to store current position in file after detecting loop/if-else block 

   a[] -> to read file
   var[] -> LHS
   var1[] -> RHS
   tm[] ->
   op[] -> operators
   ival[] ->
   tvar[] ->

*/


void dependency(char ***,int,int*,int,int);
int * storing(char ***,char *,int,int,int,int*,int,char *,char *);
void storing1(char ***,int ,int ,char * ,int ,char*,int,int,char *);
void iteration_dependency(char ***,int,int*,int);
int whi(char ***,int,int,int,int *,int,int,int);
void if_dependency(char ***,char ***,int,int,int *,int *,int);
int whi1(char ***,char ***,int,int,int *,int *,int,int);

main(){
    
    int i,ai=0,j=0,ii=0,no_row=0,k,it,flag=0,line=0,count=0,levels=8,size=0,initial=0,final=0,temp_line=0,sflag=0,ak=0,flag1=0,tflag=0;
    long curr_pos=0;
    char a[150],var[5]={'\0'},var1[5]={'\0'},tm[5]={'\0'},op[2]={'\0'},i_val[10]={'\0'},tvar[10]={'\0'};
    int ln[30],ln1[30],aflag=0;
    int * l;
    FILE *fp;

    fp=fopen("file2.c","r");
    //using a[] as buffer to scan file
    fscanf(fp,"%s",a);     		
    printf("\nRESULT.....>\n\n");

    //CALCULATING THE NO OF VARIABLES
    while(!feof(fp)){

	//checking for pf/sf in a[]
	if(strstr(a,"printf") || strstr(a,"scanf"))  
	    fscanf(fp,"%s",a);
	
	if (strstr(a,"int)") || strstr(a,"char)") || strstr(a,"float)") || strstr(a,"double)"))
	    fscanf(fp,"%s",a);
		
	if (strstr(a,"int") || strstr(a,"char") || strstr(a,"float") || strstr(a,"double")){
	    
	    j=0;
	    fscanf(fp,"%s",a);

	    while(a[j]!=';'){		
		
		//used to allocate number of blocks in dynamic array
		count++; 
		j++;
		
	    }
	
	    count++;
	
	}
	
	fscanf(fp,"%s",a);
    }

    fclose(fp);

    //DYNAMICALLY ALLOCATING THE ARRAY
    char ***arr=malloc(sizeof(char **) *levels);
    char ***arr1=malloc(sizeof(char **) *levels);

    for(i=0;i<levels;i++){
		
	arr[i]=malloc(sizeof(char *) *count);
	arr1[i]=malloc(sizeof(char *) *count);
		
	for(j=0;j<count;j++){
		
	    arr[i][j]=malloc(sizeof(char) *count);
	    arr1[i][j]=malloc(sizeof(char) *count);	
		
	} 

    }

    //READING THE FILE
    fp=fopen("file2.c","r");
    fscanf(fp,"%[^\n]\n",a);
    line++;

    while(!feof(fp)){	
	
	if(strstr(a,"printf") || strstr(a,"scanf"));
	
	else{

	    ii=0;
	    for(i=0;i<levels;i++)
		for(j=0;j<count;j++)
		    for(k=0;k<count;k++)
			memset(&arr[i][j][k],'\0',sizeof(arr[i][j][k]));
		
	    //if(strstr(a,"while") && a[strlen(a)-1]==';');

	    //OCCURENCE OF FOR/WHILE/DO-WHILE LOOP
		
	    if(strstr(a,"for") || strstr(a,"while")){	
			
		i=0;
		flag=1;
		k=0;
		//FOR LOOP
		memset(var,'\0',strlen(var));
			
		if(strstr(a,"for")){
			
		    printf("THE FOR LOOP OCCURING AT LINE NO %d ",line);
				
		    if(strstr(a,"++"))
			op[0]='+';
				
		    else
			op[0]='-';

		    while(a[i]!='\0'){

			if(a[i]=='(' && flag==1){
						
			    i++;
						
			    while(a[i]!='='){

				if(a[i]==' ');
							
				else{

				    var[k]=a[i]; //storing looping variable
				    k++;
				}
						
				i++;
						
			    }
			}
				
			if(a[i]=='=' && flag==1){

			    i++;
			    flag++;
						
			    while(a[i]!=';'){

				if(a[i]!=' '){

				    initial=(a[i]-'0')+initial;
								
				    if(a[i+1]!=' ' && a[i+1]!=';')
					initial=initial*10;
							
				}
							
				i++;				
			    }
			}
	
	
			else if((a[i]=='<' || a[i]=='>') && flag==2){

			    i++;
			    flag++;
						
			    if(a[i]=='='){

				i++;
						
			    }
						
			    while(a[i]!=';'){

				if(a[i]!=' '){

				    final=(a[i]-'0')+final;
				    if(a[i+1]!=' ' && a[i+1]!=';')
					final=final*10;
							
				}
						
				i++;				
						
			    }
					
			}
	
			i++;
		    }

		}	
				
		//WHILE LOOP
		else if(strstr(a,"while")){

		    printf("THE WHILE LOOP OCCURING AT LINE NO %d ",line);
		    curr_pos=ftell(fp);
		    k=0;
		    i=0;
		    memset(var,'\0',strlen(var));
		    memset(var1,'\0',strlen(var1));
				
		    while(a[i]!='\0'){

			if(a[i]=='('){

			    i++;
						
			    while(a[i]!='=' && a[i]!='>' && a[i]!='<' && a[i]!='!'){

				if(a[i]==' ');
							
				else{

				    var[k]=a[i];
				    k++;
							
				}
						
				i++;
			    }
						
			    k=0;
			    i++;
	
			    while(a[i]!=')'){

				if(a[i]==' ' || a[i]=='=');
							
				else{

				    var1[k]=a[i];
				    k++;
							
				}
						
				i++;
						
						
			    }
					
			}
				
			i++;
		    }
				
		    fscanf(fp,"%[^\n]\n",a);

		    memset(tm,'\0',strlen(tm));
				
		    while(!strstr(a,"}")){

			if(strlen(a)==1 && a[0]=='{'){

			    fscanf(fp,"%[^\n]\n",a);
					
			}
					
			if(a[0]=='{' && strlen(a)!=1)
			    j++;
		
			i++;
	
			k=0;
			j=0;
					
			if(strstr(a,"++") || strstr(a,"--")){
						
			    while(a[k]!='\0'){

				if(a[k]!='+' && a[k]!='-' && a[k]!=';'){

				    tm[j]=a[k];
				    j++;
								
				}
							
				k++;
						
			    }
		
			    if(!strcmp(var,tm));
						
			    else{

				memset(var,'\0',strlen(var));
				strcat(var,tm);
						
			    }
					
			}
				
			fscanf(fp,"%[^\n]\n",a);
			j=0;	
				
		    }
	
		    rewind(fp);
		    temp_line=0;
		    fscanf(fp,"%[^\n]\n",a);
		    temp_line++;
		    memset(tvar,'\0',strlen(tvar));
		    memset(i_val,'\0',strlen(i_val));
				
		    while(!feof(fp)){
				
			strcpy(tvar,var);
			strcat(tvar,"=");
					
			if(strstr(a,"while") && !strstr(a,"printf") && temp_line==line)					
			    break;
			
	
			if(strstr(a,tvar)){

			    if(!strstr(a,"int") && !strstr(a,"char") && !strstr(a,"float") && !strstr(a,"double")){

				i=0;
				k=0;
							
				while(a[i]!='='){

				    i++;
							
				}
							
				i++;
							
				while(a[i]!=';'){

				    i_val[k]=a[i];
				    k++;
				    i++;
							
				}
						
				initial=atoi(i_val);
						
			    }
					
			}
				
			fscanf(fp,"%[^\n]\n",a);
			temp_line++;
				
		    }

		    rewind(fp);
		    fseek(fp,curr_pos,1);
		}
	
		fscanf(fp,"%[^\n]\n",a);
		line++;	

		i=-1;
		k=0;
		j=0;
		ii=0;
		memset(var,'\0',strlen(var));
		memset(tm,'\0',strlen(tm));
			
		while(!strstr(a,"}")){

		    if(strstr(a,"printf") || strstr(a,"scanf")){

			fscanf(fp,"%s",a);
			line++;
				
		    }

		    if(strlen(a)==1 && a[0]=='{'){

			fscanf(fp,"%[^\n]\n",a);
			line++;
				
		    }
				
		    if(a[0]=='{' && strlen(a)!=1)
			j++;
	
		    i++;

		    ak=0;
		    it=0;
				
		    if(strstr(a,"++") || strstr(a,"--")){

			while(a[ak]!='\0'){

			    if(a[ak]!='+' && a[ak]!='-' && a[ak]!=';'){

				tm[it]=a[ak];
				it++;
						
			    }
					
			    ak++;
					
			}

			if(strstr(a,"+"))
			    op[0]='+';
				
			else
			    op[0]='-';
				
			memset(a,'\0',strlen(a));
			strcat(a,tm);
			strcat(a,"=");
			strcat(a,tm);
			strcat(a,op);
			strcat(a,"1;");
					
			if(!strcmp(var,tm));
					
			else{

			    memset(var,'\0',strlen(var));
			    strcat(var,tm);
					
			}
				
		    }
				
		    l=storing(arr,a,j,ii,line,ln,initial,var,op);
				
		    fscanf(fp,"%[^\n]\n",a);
		    line++;
		    ii++;
		    j=0;
		    k=0;
			
		}
		
		dependency(arr,i,ln,count,1);
		iteration_dependency(arr,i,ln,count);
		
	    }
	    //IF-ELSE BLOCK
	    else if(strstr(a,"if")){

		printf("THE IF-ELSE BLOCK OCCURING AT LINE %d\n",line);
		j=0;i=0;
		curr_pos=ftell(fp);
		memset(var,'\0',strlen(var));
		memset(var1,'\0',strlen(var1));
		memset(op,'\0',strlen(op));
			
		while(a[i]!='\0'){

		    if(a[i]=='('){

			i++;k=0;
					
			while(a[i]!='=' && a[i]!='>' && a[i]!='<' && a[i]!='!') {

			    if(a[i]==' ');
						
			    else{

				var[k]=a[i]; //LHS in var[]
				k++;
						
			    }

			    i++;
			}
					
			op[j]=a[i];
					
			j++;
			k=0;
			i++;
	
			while(a[i]!=')'){

			    if(a[i]==' ' || a[i]=='='){

				if(a[i]=='=')
				    op[j]=a[i];
						
			    }
						
			    else{

				var1[k]=a[i]; 	//RHS in var1[]
				k++;
						
			    }
					
			    i++;
					
			}
				
		    }
			
		    i++;
			
		}
				
				
		rewind(fp);
		temp_line=0;
		fscanf(fp,"%[^\n]\n",a);
		temp_line++;
					
		if(!atoi(var)) {

		    strcat(var,"=");
		    flag=1;
				
		}
				
		else
		    sprintf(var,"%d",initial);					
					
		if(!atoi(var1)){

		    strcat(var1,"=");							
		    flag1=1;
				
		}

		else
		    sprintf(var1,"%d",final);	
				
				
		while(!feof(fp)){

		    if(strstr(a,"while") && !strstr(a,"printf") && temp_line==line)					
			break;

		    if(flag==1){

			if(strstr(a,var)){

			    if(!strstr(a,"int") && !strstr(a,"char") && !strstr(a,"float") && !strstr(a,"double")){

				i=0;
				k=0;
								
				while(a[i]!='='){
								
				    i++;
								
				}
								
				i++;
								
				while(a[i]!=';'){
									
				    i_val[k]=a[i];
				    k++;
				    i++;
								
				}
							
				initial=atoi(i_val);
							
			    }
						
			}
					
			memset(i_val,'\0',strlen(i_val));
					
		    }
				

		    if(flag1==1){

			if(strstr(a,var1)){

			    if(!strstr(a,"int") && !strstr(a,"char") && !strstr(a,"float") && !strstr(a,"double")){

				i=0;
				k=0;
								
				while(a[i]!='='){

				    i++;
								
				}
								
				i++;
								
				while(a[i]!=';'){
								
				    i_val[k]=a[i];
				    k++;
				    i++;
								
				}
							
				final=atoi(i_val);
							
			    }
			}
					
			memset(i_val,'\0',strlen(i_val));
					
		    }

		    fscanf(fp,"%[^\n]\n",a);
		    temp_line++;
				
		}

		flag=0;
		rewind(fp);
		fseek(fp,curr_pos,1);

		if(!strcmp(op,">")){

		    if(initial>final)
			flag=1;
				
		}

		else if(!strcmp(op,"<")){

		    if(initial<final)
			flag=1;
				
		}
			
		else if(!strcmp(op,"<=")){

		    if(initial<=final){

			flag=1;
					
		    }
				
		}
				
		else if(!strcmp(op,">=")){

		    if(initial>=final)
			flag=1;
				
		}
		
		else if(!strcmp(op,"==")){

		    if(initial==final)
			flag=1;
				
		}
			
		if(flag!=1){

		    while(!feof(fp)){

			if(strstr(a,"else") && !strstr(a,"printf"))
			    break;
						
			fscanf(fp,"%[^\n]\n",a);
			line++;
					
		    }
				
		}
			
		
		fscanf(fp,"%[^\n]\n",a);
		line++;
		j=0;
		i=-1;
			
		while(!strstr(a,"}")){

		    if(strstr(a,"printf") || strstr(a,"scanf")){
				
			fscanf(fp,"%s",a);
			line++;
				
		    }

		    if(strlen(a)==1 && a[0]=='{'){
						
			fscanf(fp,"%[^\n]\n",a);
			line++;
			
		    }
				
		    if(a[0]=='{' && strlen(a)!=1)
			j++;
	
		    i++;
				
		    l=storing(arr,a,j,ii,line,ln,0," "," ");
				
		    fscanf(fp,"%[^\n]\n",a);
		    line++;
		    ii++;
		    j=0;
		    k=0;
			
		}
			
		if_dependency(arr,arr1,i,ai-1,ln,ln1,count);
		
		tflag=1;
		
	    }

	    //OCCURENCE OF ASSIGNMENT STATEMENT
	    else if ( strstr(a,";") && strstr(a,"=")){

		j=0;
	
		l=storing(arr1,a,j,ai,line,ln1,0," "," ");
		ai++;
		aflag=1;
	    }
	
	}
	
	fscanf(fp,"%[^\n]\n",a);	
	line++;
    }	

    fclose(fp);
    ai=ai-1;

    if(aflag>0 && tflag!=1){

	printf("THE FOLLOWING PAIRS OF LINES ARE DEPENEDENT AND THEREFORE CANNOT BE EXECUTED PARALLELY\n");
	dependency(arr1,ai,ln1,count,0);
    }

    printf("\n\n");

    for(i=1;i<levels;i++){

	for(j=0;j<count;j++){

	    free(arr[i][j]);
	    free(arr1[i][j]);
	
	}
	
	free(arr[i]);
	free(arr1[i]);

    }

    free(arr);
    free(arr1);
}

//END OF MAIN

//FUNCTION FOR CHECKING DEPENDENCY
void dependency(char *** arr,int no_row,int * ln,int count,int sflag){

    int i,ii,j,k,flag=0,it;
    char *test=malloc(sizeof(int) * count);

    for(i=0;i<=no_row;i++){

	for(ii=0;ii<=no_row;ii++){

	    if(i==ii){

		continue;
		
	    }

	    j=0;
			
	    while(arr[1][ii][j]!='\0'){

		k=0;
				
		while(arr[1][ii][j]!=' ' && arr[1][ii][j]!='\0'){

		    test[k]=arr[1][ii][j];
		    j++;
		    k++;
			
		}
					
		if(!atoi(test)){

		    if (!strcmp(arr[0][i],test)){

			if(sflag==1)		
			    printf("CANNOT BE EXECUTED PARALLELY (ASSIGNMENT-WISE) AS DEPENDENCY EXISTS BETWEEN THE\n");
					
			printf("LINE %d and LINE %d (READ AFTER WRITE)\n",ln[i],ln[ii]);
			flag++;
		    }		
				
		    else;
				
		}

		for(it=0;it<=k;it++) {
			
		    test[it]='\0';
			
		}
		
		j++;
		
	    }
		
	    j=0;
		
	    if(sflag==1){

		while(arr[3][ii][j]!='\0'){

		    k=0;
				
		    while(arr[3][ii][j]!=' ' && arr[3][ii][j]!='\0'){

			test[k]=arr[3][ii][j];
			j++;
			k++;
				
		    }
						
		    if(!atoi(test)){
				
			if (!strcmp(arr[2][i],test)){

			    if(flag==0){

				printf("CANNOT BE EXECUTED PARALLELY (ASSIGNMENT-WISE) AS DEPENDENCY EXISTS BETWEEN THE\n");
						
			    }
					
			    printf("LINE %d and LINE %d (READ AFTER WRITE)\n",ln[i],ln[ii]);
			
			    flag++;
					
			}		
					
			else;
					
		    }
	
		    for(it=0;it<=k;it++){

			test[it]='\0';
				
		    }
			
		    j++;
			
		}
		
	    }					
	
	}

    }		
	
    if (flag==0 && sflag==1)
	printf("CAN BE EXECUTED PARALLELY (ASSIGNMENT-WISE)\n");

    free(test);
}

//FUNCTION FOR STORING IN THE 3-D ARRAY
int* storing(char *** arr,char * a ,int j,int ii,int line,int *ln,int initial,char * var,char * op){

    int k=0,st1,st2,kk=0,aa=0;
    char test[20]={'\0'};
	
    while(a[j]!='='){

	if(a[j]=='['){

	    while(a[j]!=']'){

		arr[0][ii][k]=a[j];
		j++;
		k++;
			
	    }
		
	    arr[0][ii][k]=a[j];
		
	}

	if (a[j]=='+'||a[j]=='-'||a[j]=='/'||a[j]=='*'||a[j]=='%'||a[j]=='&'||a[j]=='|'||a[j]=='^'||a[j]=='<'||a[j]=='>')
	    j++;
					
	arr[0][ii][k]=a[j];
		
				
	ln[ii]=line;	
	k++;
	j++;

    }

    if(strcmp(var," ")){

	strcpy(test,arr[0][ii]);
	storing1(arr,ii,0,var,initial,test,0,0,op);
	memset(test,'\0',strlen(test));
	
    }

    j++;
    k=0;
    st1=0;
    st2=0;
    kk=0;

    while(a[j]!='\0'){

	if(a[j]=='['){
	    while(a[j]!=']'){

		arr[1][ii][k]=a[j];
		test[kk]=a[j];
		j++;
		k++;
		kk++;
				
	    }
		
	    arr[1][ii][k]=a[j];
		
	    test[kk]=a[j];
		
	}
				
	else if (a[j]=='+'||a[j]=='-'||a[j]=='/'||a[j]=='*'||a[j]=='%'||a[j]=='&'||a[j]=='|'||a[j]=='^'||a[j]=='<'||a[j]=='>'||a[j]==';'){
	    arr[1][ii][k]=' ';
			
	    if(strcmp(var," ")){

		storing1(arr,ii,1,var,initial,test,st1,st2,op);
		memset(test,' ',strlen(test));
			
		st1=strlen(arr[3][ii]);
		st2=strlen(arr[5][ii]);
			
	    }
		
	    kk=0;
		
	}

	else if(a[j]==';'){

	    if(strcmp(var," ")){

		storing1(arr,ii,1,var,initial,test,st1,st2,op);
			
	    }
		
	}	
		
	else{

	    arr[1][ii][k]=a[j];
	    test[kk]=a[j];
		
	}
		
	j++;
	k++;
	kk++;
    } 

    return(ln);	

}

//FUNCTION FOR STORING VALUE OF ITERATION IN 3D ARRAY 
void storing1(char ***arr,int ii,int i,char * var,int initial,char* test,int st1,int st2,char * opr){

    int jj,k,t,flag=0,tempjj,res=0,ope1=0,occ[10]={0},o=0,ope2=0,fflag=0;
    char cres[10]={'\0'},op;

    if(strstr(test,var)){

	for(jj=0;test[jj]!='\0';jj++){
		
	    flag=0;		
			
	    for(k=0,t=jj;k<strlen(var),test[t]!='\0';k++,t++){

		if(test[t]==var[k])
		    flag++;

		if(flag==strlen(var)){

		    occ[o]=t-strlen(var);
		    o++;			
		    break;
			
		}
		
	    }
		
	}

    }	

    if(strstr(test,"[")){

	t=0;	
	o=0;
	
	while(test[t]!='['){

	    t++;
	}
	
	tempjj=t;
	
	while(test[t]!=']'){

	    ope1=0;
	    ope2=0;
		
	    if(fflag==0){
		while(test[t]!='+'&&test[t]!='-'&&test[t]!='/'&&test[t]!='*'&&test[t]!='%'&&test[t]!=']'){

		    if (t==occ[o]){

			o++;
			t=t+strlen(var)+1;
			ope1=initial;
			break;
				
		    }
								
		    else{

			t++;
					
			if(test[t]!='+'&&test[t]!='-'&&test[t]!='/'&&test[t]!='*'&&test[t]!='%'){

			    ope1=ope1*10;	
			    ope1=(test[t]-'0')+ope1;
						
			}
				
		    }
			
		}
			
		res=ope1;
		fflag++;
	    }
		
	    if(test[t]==']');
		
	    else{

		if(test[t]=='+' || test[t]=='-' || test[t]=='/' || test[t]=='*' || test[t]=='%'){

		    op=test[t];
			
		}
	
		if (occ[o]==t){

		    o++;
		    t=t+strlen(var)+1;
		    ope2=initial;
			
		}
			
		else{

		    t++;
				
		    while(test[t]!='+'&&test[t]!='-'&&test[t]!='/'&&test[t]!='*'&&test[t]!='%'&&test[t]!=']'){
					
			ope2=ope2*10;						
			ope2=(test[t]-'0')+ope2;
			t++;
				
		    }
			
		}
		
		switch(op){

		case 43:{

		    res=res+ope2;
		    break;		
				
		}
				
		case 45:{

		    res=res-ope2;
		    break;
				
		}
				
		case 47:{

		    res=res/ope2;
		    break;
				
		}
				
		case 42:{

		    res=res*ope2;
		    break;
				
		}
				
		case 37:{

		    res=res%ope2;
		    break;
				
		}
		}
	    }
	}
	
	t++;
	
	sprintf(cres,"%d",res);
		
	for(k=0;k<=tempjj;k++){

	    arr[i+2][ii][st1]=test[k];
	    st1++;
			
	}

	for(k=0;k<=tempjj;k++){

	    arr[i+4][ii][st2]=test[k];
	    st2++;
		
	}


	strcat(arr[i+2][ii],cres);

	if(opr[0]=='+'){
		
	    res=res+1;
	
	}
		
	else{

	    res=res-1;
		
	}
	
	sprintf(cres,"%d",res);
	strcat(arr[i+4][ii],cres);
	strcat(arr[i+2][ii],"]");
	strcat(arr[i+4][ii],"]");

    }
}

//FUNCTION FOR CHECKING DEPENDENCY IN TWO ITERATIONS OF A LOOP
void iteration_dependency(char *** arr,int no_row,int * ln,int count){
	
    int i,ii,j=0,k,flag=0,it;
    char *test=malloc(sizeof(int) * count);

    for (i=0;i<=no_row;i++){

	for(ii=0;ii<=no_row;ii++){

	    if(!strcmp(arr[2][i],"") && !strcmp(arr[4][ii],""));
			
	    else{

		if(!strcmp(arr[2][i],arr[4][ii])){

		    printf("AND CANNOT BE EXECUTED PARALLELY (ITERATION WISE) ");
		    printf("AS DEPENDENCY EXISTS BETWEEN TWO ITERATIONS OF THE LOOP\n");
		    printf("IN LINE %d and LINE %d (WRITE AFTER WRITE DEPENDENCY)\n",ln[i],ln[ii]);
		    flag=1;
		}
	    }
	}
    }


    for(ii=0;ii<=no_row;ii++){

	flag=whi(arr,5,ii,count,ln,2,no_row,flag);
	flag=whi(arr,3,ii,count,ln,4,no_row,flag);

    }

    if(flag==0){

	printf("AND CAN BE EXECUTED PARALLELY (ITERATION WISE)\n");
	flag++;
    }

    printf("\n\n");
    free(test);
}

	
//FUNCTION FOR CHECKING DEPENDENCY IN TWO ITERATIONS OF A LOOP (read-write)
int whi(char ***arr,int i,int ii,int count,int * ln,int ij,int no_rows,int flag){
	
    char *test=malloc(sizeof(int) * count);
    int j=0,k,ik;
		
    while(arr[i][ii][j]!='\0'){

	k=0;
		
	while(arr[i][ii][j]!=' ' && arr[i][ii][j]!='\0'){

	    test[k]=arr[i][ii][j];
	    j++;
	    k++;
	}

	if(!atoi(test)){

	    for(ik=0;ik<=no_rows;ik++){

		if((!strcmp(arr[ij][ik],"") && !strcmp(test,"")));
					
		else{
						
		    if (!strcmp(arr[ij][ik],test)){

			if(flag==0){
								
			    printf("AND CANNOT BE EXECUTED PARALLELY (ITERATION WISE) ");	
			    printf("AS DEPENDENCY EXISTS BETWEEN ANY TWO ITERATIONS OF THE LOOP\n");
			    printf("IN LINE %d and LINE %d (READ AFTER WRITE DEPENDENCY)\n",ln[ik],ln[ii]);
			    flag++;
					
			}
							
			else{
						
			    printf("AND IN LINE %d and LINE %d (READ AFTER WRITE DEPENDENCY)\n",ln[ik],ln[ii]);
			    flag++;
							
			}
						
		    }
					
		    else;
					
		}
	
	    }
	
	}	
	
	j++;
    }
	
    free(test);
    return(flag);
}


//FUNCTION FOR CHECKING DEPENDENCY IN IF-ELSE BLOCK AND ASSIGNMENT STATEMENT BLOCK ABOVE IT
void if_dependency(char *** arr,char *** arr1,int no_row1,int no_row2 ,int * ln,int * ln1,int count){

    int i,ii,j=0,k,flag=0,it;
    char *test=malloc(sizeof(int) * count);

    for (i=0;i<=no_row1;i++){

	for(ii=0;ii<=no_row2;ii++){

	    if(!strcmp(arr[0][i],"") && !strcmp(arr1[0][ii],""));
			
	    else{

		if(!strcmp(arr[0][i],arr1[0][ii])){

		    printf("CANNOT BE EXECUTED PARALLELY (IF) ");
		    printf("AS DEPENDENCY EXISTS BETWEEN THE IF ELSE BLOCK AND THE ASSIGNMENT STATEMENT (IF)\n");
		    printf("IN LINE %d (OF IF-ELSE BLOCK) and LINE %d (WRITE AFTER WRITE DEPENDENCY)\n",ln[i],ln1[ii]);
		    flag=1;
		}
	    }
	}
    }


    for(ii=0;ii<=no_row1;ii++){

	flag=whi1(arr,arr1,ii,count,ln,ln1,no_row2,flag);
    }

    for(ii=0;ii<=no_row2;ii++){

	flag=whi1(arr1,arr,ii,count,ln1,ln,no_row1,flag);
    }


    if(flag==0){

	printf("CAN BE EXECUTED PARALLELY WITH THE ASSIGNMENT BLOCK\n");
	flag++;
    }

    printf("\n\n");
    free(test);
}

//FUNCTION FOR CHECKING DEPENDENCY IN IF-ELSE BLOCK AND ASSIGNMENT STATEMENT BLOCK ABOVE IT
int whi1(char ***arr,char *** arr1,int ii,int count,int * ln,int * ln1,int no_rows,int flag){

    char *test=malloc(sizeof(int) * count);
    int j=0,k,ik;
		
    while(arr[1][ii][j]!='\0'){

	k=0;
		
	while(arr[1][ii][j]!=' ' && arr[1][ii][j]!='\0'){	
	    test[k]=arr[1][ii][j];
	    j++;
	    k++;
	}

	if(!atoi(test)){

	    for(ik=0;ik<=no_rows;ik++){

		if((!strcmp(arr1[0][ik],"") && !strcmp(test,"")));
					
		else{

		    if (!strcmp(arr1[0][ik],test)){

			if(flag==0){

			    printf("CANNOT BE EXECUTED PARALLELY ");	
			    printf("AS DEPENDENCY EXISTS BETWEEN THE IF ELSE BLOCK AND THE ASSIGNMENT STATEMENT ");
			    printf("IN LINE %d and LINE %d (OF IF-ELSE BLOCK) (READ AFTER WRITE DEPENDENCY)\n",ln1[ik],ln[ii]);
			    flag++;
							
			}
							
			else{
						
			    printf("AND IN LINE %d and LINE %d (OF IF-ELSE BLOCK) (READ AFTER WRITE DEPENDENCY)\n",ln1[ik],ln[ii]);
			    flag++;
			}
		    }
					
		    else;
					
		}
	
	    }
	
	}	
	
	j++;
	
    }
	
    free(test);
    return(flag);

}
