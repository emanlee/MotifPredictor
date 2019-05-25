#include <string.h>
#include <ctype.h>

#ifndef MAX_LINE_LENGTH  
#define MAX_LINE_LENGTH 5000  
#endif 
 

#ifndef __pairnode
#define __pairnode
struct pairnode
{
	char left[50];
	char right[50];   
 
};
#endif 


char * strtolower(char * old)
{
	// get lower case
    char xx[1000];
    char *p=xx;
    int ii, length=0;
    length=strlen(old);
    for(ii=0; ii<length; ii++)
    {
        xx[ii]=tolower(old[ii]);
    }
	xx[ii]='\0';

    return p;

}



long file_line_count(char file_name[])
{
	/* 
	Purpose: Count the lines of a file 
	Input: File name
	Output: Number of lines
	*/
	
	char *buff_data;
	FILE *fid_1;
	long row=0;
	
	buff_data=(char*)malloc(MAX_LINE_LENGTH*sizeof(char));
	
	fid_1=fopen(file_name,"r"); 
	if(fid_1==NULL)
	{
		printf("cannot open %s\n",file_name);		
		return -1;
	}
	
	while(!feof(fid_1))
	{
		if(fgets(buff_data,MAX_LINE_LENGTH,fid_1)==NULL)
		{
			//puts("read failed!\n");	
			break;		 
		}
		row++;
	}
	fclose(fid_1);
	free(buff_data);/* free */
	return row;
}



void load_files(char input_file_uniq[], struct pairnode * pp_uniq, 
	long *valid_row_count_uniq)
{
	/* 
	Purpose: Load a file which consists of two columns (forming pairs of regulational relationship)
	Input: File name; Pointer to structure of pair nodes; Pointer to number of pairs
	Output: Storing pairs in the memory (Pointer to structure of pair nodes)
	*/
	FILE *fid_input_file_uniq;  
	long rowindex=0;
	char chr[200], *p;

	// read  file and process
	fid_input_file_uniq=fopen(input_file_uniq, "r"); 
	if(fid_input_file_uniq==NULL)
	{
		printf("cannot open file: %s.\n",input_file_uniq);	
		return  ;
	}
	
 
	while(!feof(fid_input_file_uniq))
	{
		if(fgets(chr, 200, fid_input_file_uniq)!=NULL)
		{

			//sequence
			if (chr[strlen(chr)-1]==13 || chr[strlen(chr)-1]==10)
			{
				chr[strlen(chr)-1]='\0';
			}
			else
			{
				chr[strlen(chr)]='\0';
			}



			if(strlen(chr)>=3)
			{
				
				p=strtok(chr, " \t");
				sscanf(p, "%s", pp_uniq[rowindex].left);
				p=strtok(NULL, " \t");
				sscanf(p, "%s", pp_uniq[rowindex].right);
							
				
				
				
				rowindex++;
			}	
		 

		}
	}

	*valid_row_count_uniq=rowindex;
	fclose(fid_input_file_uniq);

	// for check
	/*for(rowindex=0; rowindex<10; rowindex++)
	{
		printf("%s %s\n", pp_uniq[rowindex].left, pp_uniq[rowindex].right);
	}*/

	printf("row_count:%ld\n\n",*valid_row_count_uniq);

  
}



void get_model( struct pairnode * miRNA2tfnodes,   long row_count_1,
				struct pairnode * tf2genenodes,    long row_count_2,
				struct pairnode * miRNA2genenodes, long row_count_3,
				char  output_file[]
				)
{
	/* 
	Purpose: Get models(motifs) 
	Input: Pointer to structure of pair nodes; Numbers of pairs; File name of output
	Output: Results are to be printed in a file
	*/
	// *tf2miRNAnodes,  *tf2genenodes, *miRNA2genenodes
		
	long fllcount=0, xx, yy, zz ;
	 
 	FILE *fid_output ;  
 
	
	fid_output=fopen(output_file,"w"); 
	if(fid_output==NULL)
	{
		printf("ERROR: cannot open %s\n",output_file);	 
		return ;
	}
	
		printf("Motifs:\n");
	// for check
	for(xx=0; xx<row_count_1; xx++) // miRNA2tfnodes
	{
		//printf("xx:%ld ",xx);
		for(yy=0; yy<row_count_3; yy++) // miRNA2genenodes
		{
			 //printf("yy:%ld ",yy);
//			 if(yy==5177)
//			 	temp=0;
			 if(strcmp(miRNA2tfnodes[xx].left, miRNA2genenodes[yy].left)==0)
			 {
				for(zz=0; zz<row_count_2; zz++) // tf2genenodes
				{
//					if(yy==5177)
//						{
//							printf("zz:%ld ",zz);
//							printf("%s %s %s %s ",
//							 tf2genenodes[zz].left,  miRNA2tfnodes[xx].left,
//					 	     tf2genenodes[zz].right, miRNA2genenodes[yy].right );
//							 
//						}
					 if(	strcmp(tf2genenodes[zz].left,  miRNA2tfnodes[xx].right)==0
					 	&&  strcmp(tf2genenodes[zz].right, miRNA2genenodes[yy].right)==0
					 )
					 {
						 
						  fllcount++;
						  
						  	fprintf(fid_output, "%s~%s, %s~%s, %s~%s\n", 
							  miRNA2tfnodes[xx].left , miRNA2tfnodes[xx].right,
							 tf2genenodes[zz].left, tf2genenodes[zz].right,
							  miRNA2genenodes[yy].left , miRNA2genenodes[yy].right 
							  )	;
							printf ("%s~%s, %s~%s, %s~%s\n", 
							 miRNA2tfnodes[xx].left , miRNA2tfnodes[xx].right,
							 tf2genenodes[zz].left, tf2genenodes[zz].right,
							  miRNA2genenodes[yy].left , miRNA2genenodes[yy].right 
							 
						  )	;  
					 }
				} 	
			 }
		}
	}

	printf("Motif count:%ld\n\n",fllcount);
	fclose(fid_output);
  
}
 
 

