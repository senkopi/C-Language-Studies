#include "database.h"

int initDatabase()
{
	dbFile = fopen("./database.txt", "a+");
	if(dbFile == NULL)
	{
		return -1;
	}
	readPatients();
	return 0;
}

void clearDatabase()
{
	freopen("./database.txt",  "w+", dbFile);
}
void closeDatabase()
{
	fclose(dbFile);
}

Patient* getPatients()
{
	updateDatabase();
	return patients;
}
int readPatients()
{
	//First line is the last id
	rewind(dbFile);
	int lineNumber = 0;

	while(!feof(dbFile))
	{	

		if(lineNumber == 0)
		{
			int check = fscanf(dbFile, "%d\n", &lastId); //that \n is needed
			if(check==0)
			{
				lastId = 0; //Couldn't read. Possivle empty file
			}
		}else{
			int id;
			char nameBuffer[50];
			char surnameBuffer[50];
			char birthdayBuffer[50];
			char emailBuffer[100];
			char departmentBuffer[50];
			int check = fscanf(dbFile, "%d %s %s %s %s %s", &id, nameBuffer, surnameBuffer, birthdayBuffer, emailBuffer, departmentBuffer);
			if(check == 6)
			{
				Patient patient = createPatient(nameBuffer, surnameBuffer, birthdayBuffer, emailBuffer, departmentBuffer);
				patientIndex++;
				patients[patientIndex] = patient;
			}
		}
		lineNumber++;
	}
}
int getPatientNumber()
{
	//printf("deletedPatients: %d\n", deletedPatients);
	return (patientIndex+1- deletedPatients);
}
void updateDatabase()
{
	clearDatabase();
	rewind(dbFile);
	fprintf(dbFile, "%d\n", lastId);
	int i;
	for(i=0;i<patientIndex+1;i++)
	{

		Patient patient = patients[i];
		fprintf(dbFile, "%d %s %s %s %s %s\n", patient.id, patient.name, patient.surname, patient.birthday, patient.email, patient.department);
	}
}
int addPatient(char* name, char* surname, char* birthday, char* email, char* department)
{
	Patient newPatient = createPatient(name, surname, birthday, email, department);
	newPatient.id = lastId;
	lastId++;
	patientIndex++;
	patients[patientIndex] = newPatient;
	updateDatabase();
}

