#define _GNU_SOURCE
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"


int reductor(FILE * fp, FILE * fop)
{
	char line[200] ;
	size_t num = 200;
	ssize_t read;
	float vmed[70]; 
	float imed[70]; 
	float pot=0;
	float isum=0;
	float iaemed[70];
	float vacmed[70];
	float iacmed[70];
	float iaemeds=0;
	float iacmeds=0;
	float vacmeds=0;
	char fecha[16];
	char hora[16];
	char fechactual[16];
	char horactual[16];
	char tmp[16];
	char * pch;
	int i,j;

	rewind(fp);

	for (i=1; i<16; i++ )
		fgets(line, num, fp); //""saltea" lineas
		
	


	i=0;

	pch=strtok(line," ,");//regno

	pch = strtok(NULL," ,");//fecha
	strcpy(fecha,pch);
	strcpy(fechactual,pch);

	pch = strtok(NULL," ,");//Hora
	strcpy(hora,pch);
	strcpy(horactual,pch);

	pch = strtok(NULL," ,");//vbmed
	vmed[0]  =  atof (pch);//vbmed

	pch = strtok(NULL," ,");//iaemed
	iaemed[0]  =  atof (pch);//iaemed

	pch = strtok(NULL," ,");//vacmed
	vacmed[0]  =  atof (pch);//vacmed

	pch = strtok(NULL," ,");//	iacmed
	iacmed[0]  =  atof (pch);//iacmed

	pch = strtok(NULL," ,");//ipvmed
	imed[0]  =  atof (pch);//ipvmed

	pch = strtok(NULL," ,");//rpmmed
	pch = strtok(NULL," ,");//tmed
	pch = strtok(NULL," ,");//SI1-SI0
	pch = strtok(NULL," ,");//SV1-SV0
	pch = strtok(NULL," ,");//DOS_PA
	pch = strtok(NULL," ,");//DOS_ST
	pch = strtok(NULL," ,");//FRE_ST
	pch = strtok(NULL," ,");//SMOKE
	pch = strtok(NULL," ,");//DOOR
	pch = strtok(NULL," ,");//CONTAC
	pch = strtok(NULL," ,");//STATUS
	







//	printf("%s %s %f %f\n",fecha,hora,vmed[0],imed[0] );

	
			

//encabezado


	while ((fgets(line, num, fp)) != NULL) {
		pch = strtok(line, " ,");//regno
		pch = strtok(NULL, " ,");//fecha
		strcpy(fecha, pch);
		pch = strtok(NULL, " ,");//hora
		strcpy(hora, pch);
		
		if( (strncmp(horactual,hora,2)!= 0) || (0!=strcmp(fechactual,fecha))) { 
			//cambio la hora!
		//	printf("%s %s %s %s\n",hora,horactual,fecha,fechactual);
#if 1
			pot=0;
			isum=0;
			vacmeds=0;
			iaemeds=0;
			iacmeds=0;
			for(j=0; j<i; j++){
				pot += vmed[j]*imed[j];
				isum += imed[j];
				vacmeds += vacmed[j];
				iaemeds += iaemed[j];
				iacmeds += iacmed[j];
			//	if (pot>1)
			//		printf("v %f\ti %f\t : pot=%f \n",vmed[j],imed[j],pot/i);
			}

			fprintf(fop,"%s, %s, %f, %f, %f, %f, %f, %f, %f, %f\n", fechactual, horactual,
				pot/60,	pot/i, isum/60, isum/i, iaemeds/60, iaemeds/i,
			       	iacmeds/60, iacmeds/i);
			strcpy(horactual,hora);
			strcpy(fechactual,fecha);

			for(j=0; j<70; j++){
				vmed[j] = 0;
				imed[j] = 0;
				vacmed[j] = 0;
				iaemed[j] = 0;
				iacmed[j] = 0;
			}

			i=1;	
			//vmed[0]  =  atoi (&line[29]);
			//imed[0]  =  atoi (&line[52]);
			pch = strtok(NULL," ,");//vbmed
			vmed[0]  =  atof (pch);//vbmed

			pch = strtok(NULL," ,");//iaemed
			iaemed[0]  =  atof (pch);//iaemed

			pch = strtok(NULL," ,");//vacmed
			vacmed[0] = atof(pch);//vacmed

			pch = strtok(NULL," ,");//iacmed
			iacmed[0]  =  atof (pch);//iacmed

			pch = strtok(NULL," ,");//ipvmed
			imed[0]  =  atof (pch);//ipvmed

		} else { 
			//misma hora
		//	vmed[i]  =  atoi (&line[29]);
		//	imed[i]  =  atoi (&line[52]);
			pch = strtok(NULL," ,");//vbmed
			vmed[i]  =  atof (pch);//vbmed

			pch = strtok(NULL," ,");//iaemed
			iaemed[i]  =  atof (pch);//iaemed

			pch = strtok(NULL," ,");//vacmed
			vacmed[i] = atof(pch);//vacmed

			pch = strtok(NULL," ,");//iacmed
			iacmed[i]  =  atof (pch);//iacmed

			pch = strtok(NULL," ,");//ipvmed
			imed[i]  =  atof (pch);//ipvmed

			i++;
#endif
		}

		strtok(pch, line);////////////////////////////////////


	}// end while


			//ultima hora!
			pot=0;
			isum = 0;
			vacmeds = 0;
			iaemeds = 0;
			iacmeds = 0;
			for(j=0; j<i; j++){
				pot += vmed[j]*imed[j];
				isum += imed[j];
				vacmeds += vacmed[j];
				iaemeds += iaemed[j];
				iacmeds += iacmed[j];
			}


			fprintf(fop,"%s, %s, %f, %f, %f, %f, %f, %f, %f, %f\n", fecha, hora, pot/60,
				pot/i, isum/60, isum/i, iaemeds/60, iaemeds/i, iacmeds/60, iacmeds/i);
					


	return EXIT_SUCCESS;
}



int main(void)
{
	DIR *dir;
	struct dirent *ent;
	char *pch;
	FILE *fpin;// puntero a lista
	FILE *fpout;// archivo de salida

	fpout = fopen("salida.csv","w+");
	if ( fpout==NULL )  {
	   	printf("error fopen\n");
	    return -1;
	}

	fprintf(fpout,"fecha, hora, energia, promedio potencia, IPVMED/60, IPVMED promedio,\
IAEMED/60, IAEMED promedio,IACMED/60, IACMED promedio,\n" );
	dir = opendir (".");
	if (dir != NULL) {

		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {

			if( ent->d_name[0]=='P') {
				pch= (char *) memchr(ent->d_name, '.', strlen(ent->d_name));
				if (pch != NULL) {
					pch++;
					if ( (!strcmp(pch,"CSV"))
							|| (!strcmp(pch,"csv"))
							|| (!strcmp(pch,"Csv"))
					   )   {
						fpin = fopen(ent->d_name,"r");
						if ( fpout==NULL )  {
							printf("error fopen\n");
						} else {
							printf ("\nprocesando: %s\n", ent->d_name);
							reductor(fpin, fpout);
							fclose(fpin);
						}
					}
				}
			}
		}
		fclose(fpout);
		closedir (dir);
	} else {
		/* could not open directory */
		return -1;
	}
}


