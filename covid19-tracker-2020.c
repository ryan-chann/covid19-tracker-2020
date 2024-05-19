/*
   Program Name : covid19-tracker-2020.c
   Written By : Ryan Chan Joon Yew
   Date : 27/7/2020
   Purpose : To record daily number of covid-19 cases
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#pragma warning (disable: 4996)

//Previous day's data constants
#define DAY1_NEW_CASES 9
#define DAY1_TOTAL_CASES  100
#define DAY1_TOTAL_DEATHS 2
#define DAY1_TOTAL_RECOVERED 10
#define DAY1_TOTAL_UNDER_TREATMENT 88

//Global Variable Declaration
int importedCases, localCases, deaths, recovered;//Input Cases Data
int totalNewCases = 0, casesGap, totalNewCases, totalPreviousCases;//To Calculate the difference between Current and Previous cases
int daycount = 2, previousDaycount = 1;//To update the days
int choice;//Selection for the user to print which report
char selection;//Selection for the user to end the program
int totalCases = 0, totalDeaths, totalRecovered, totalUnderTreatment;//Daily Summary Report Variables
double totalDeathsPercentage, totalRecoveredPercentage, underTreatmentPercentage;//Daily Summary Report Variables
double previousDaytotalDeathsPercentage, previousTotalRecoveredPercentage;//To Calculate the previous case Percentage
int previousCases, previousTotalDeaths, previousTotalRecovered;//Calculate previous day's cases, deaths and recovered
double deathPercentageDifference, totalRecoveredPerecentageDifference;//2ndOutput
int totalCasesDifference;//Calculate the difference between previous day cases and current day cases
int highestCase = -99999999, lowestCase = 99999999;//To calculate the highest case and lowest case
int highestCaseDay = 0, lowestCaseDay = 0;//To calculate the days occurs highest case and lowest case
int option;//Menu Option

//Function Declaration
void logo();
void title();
void credits();
void previoustotal();
void day2();
void menu();

void main()
{
	logo();
	title();
	do {
		menu();
		scanf("%d", &option);
		switch (option) {
		case 1: {
			previoustotal();
			break;
		}
		case 2:
			day2();
			break;
		case 3:
			credits();
			break;
		default:
			printf("Error ! Please go back menu to enter your choice again\n");
		}
	} while (option != 2);
	system("pause");
}


void menu() {
	printf("%7.sMenu\n", NULL);
	printf("=====================\n");
	printf("1.Show Previous Day Summary Report \n");
	printf("2.Update Covid-19 Report \n");
	printf("3.Credits\n");
	printf("Enter here : ");
}

void title()
{
	printf("%20.sCOVID-19 CASES TRACKING SYSTEM\n");
	printf("%15.s======================================\n");
	printf("%20.s***Welcome to CCTP System***\n");
}

void logo()
{
	printf("\033[1;34m");
	printf("%15.s+---------------------------------------+\n", NULL);
	printf("%15.s| #########%1.s#########%1.s########%2.s#######%1.s|\n", NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #%9.s#%13.s#%5.s#%5.s#%1.s|\n", NULL, NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #%9.s#%13.s#%5.s#%5.s#%1.s|\n", NULL, NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #%9.s#%13.s#%5.s#######%1.s|\n", NULL, NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #%9.s#%13.s#%5.s#%7.s|\n", NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #%9.s#%13.s#%5.s#%7.s|\n", NULL, NULL, NULL, NULL, NULL);
	printf("%15.s| #########%1.s#########%5.s#%5.s#%7.s|\n", NULL, NULL, NULL, NULL, NULL);
	printf("%15.s+---------------------------------------+\n", NULL);
	printf("\033[0m");
}


void credits()
{
	printf("\033[1;34m");
	printf("\nThis Covid-19 Cases Tracking System is brought to you by Ryan Chan Joon Yew\n\n");
	printf("\033[0m");
}


void previoustotal()
{
	//Process
	totalDeathsPercentage = (double)DAY1_TOTAL_DEATHS / DAY1_TOTAL_CASES * 100;
	totalRecoveredPercentage = (double)DAY1_TOTAL_RECOVERED / DAY1_TOTAL_CASES * 100;
	underTreatmentPercentage = (double)DAY1_TOTAL_UNDER_TREATMENT / DAY1_TOTAL_CASES * 100;
	//Placeholder
	previousCases = DAY1_NEW_CASES;
	totalPreviousCases = DAY1_TOTAL_CASES;
	previousTotalDeaths = DAY1_TOTAL_DEATHS;
	previousTotalRecovered = DAY1_TOTAL_RECOVERED;
	previousTotalRecoveredPercentage = totalRecoveredPercentage;
	previousDaytotalDeathsPercentage = totalDeathsPercentage;

	//Output
	printf("%7.sYesterday's Totals - (Day 1) : \n");
	printf("+----------------------+-------------++--------+-----------+------------+\n");
	printf("|%7.sYesterday's%4.s|%1.sTotal Cases%1.s||%1.sTotal%2.s|%3.sTotal%3.s|%4.sUnder%3.s|\n");
	printf("|%7.sCases%10.s|%13.s||%1.sdeaths%1.s|%1.sRecovered%1.s|%2.streatment%1.s|\n");
	printf("+----------------------+-------------++--------+-----------+------------+\n");
	printf("|%17.d%5.s|%8.d%5.s||%5.d%3.s|%6.d%5.s|%7.d%5.s|\n", DAY1_NEW_CASES, NULL, DAY1_TOTAL_CASES, NULL, DAY1_TOTAL_DEATHS, NULL, DAY1_TOTAL_RECOVERED, NULL, DAY1_TOTAL_UNDER_TREATMENT, NULL);
	printf("+-----------------------------------------------------------------------+\n");
	printf("%37.s||%1.s%.1f%%%3.s|%2.s%.1f%%%4.s|%3.s %.1f%%%3.s|\n", NULL, NULL, previousDaytotalDeathsPercentage, NULL, NULL, totalRecoveredPercentage, NULL, NULL, underTreatmentPercentage, NULL);
	printf("%37.s++---------------------------------+\n", NULL);
	printf("\033[1;31m");
	printf("------------------------ End of Day 1 Reporting -------------------------\n");
	printf("\033[0m");


}

void day2()
{
	//Process
	totalDeathsPercentage = (double)DAY1_TOTAL_DEATHS / DAY1_TOTAL_CASES * 100;
	totalRecoveredPercentage = (double)DAY1_TOTAL_RECOVERED / DAY1_TOTAL_CASES * 100;
	underTreatmentPercentage = (double)DAY1_TOTAL_UNDER_TREATMENT / DAY1_TOTAL_CASES * 100;

	//Placeholder
	previousCases = DAY1_NEW_CASES;
	totalPreviousCases = DAY1_TOTAL_CASES;
	previousTotalDeaths = DAY1_TOTAL_DEATHS;
	previousTotalRecovered = DAY1_TOTAL_RECOVERED;
	previousTotalRecoveredPercentage = totalRecoveredPercentage;
	previousDaytotalDeathsPercentage = totalDeathsPercentage;


	do {

		//Input
		printf("Day %d\n", daycount);
		printf("=======\n");
		printf("Key in Today's data%1.s:%1.s\n", NULL, NULL);

		printf("%8.sNo. of new local cases%4.s: ", NULL, NULL);
		scanf("%d", &localCases);

		printf("%8.sNo. of new imported cases : ", NULL);
		scanf("%d", &importedCases);

		//Process
		totalNewCases = localCases + importedCases;
		casesGap = totalNewCases - previousCases;

		//Output
		if (totalNewCases > previousCases)
			printf("Total no. of new cases = %d%6.s(Increase by %d from yesterday.)\n", abs(totalNewCases), NULL, abs(casesGap));
		else if (totalNewCases < previousCases)
			printf("Total no. of new cases = %d%6.s(Decrease by %d from yesterday.)\n", abs(totalNewCases), NULL, abs(casesGap));
		else if (totalNewCases == previousCases)
			printf("Total no. of new cases = %d%6.s(There is no changes from yesterday.)\n", abs(totalNewCases), NULL);


		//2ndInput
		printf("Enter number of deaths > ");
		scanf("%d", &deaths);

		printf("Enter number of recovered / discharged > ");
		scanf("%d", &recovered);

		printf("\n1 - Daily Summary Report,%9.s2 - Daily Comparative Report\n", NULL);
		printf("What type of Report would you like to view (Choose 1 or 2)? > ");
		scanf("%d", &choice);



		//Daily Summary Report Process
		totalCases = totalPreviousCases + totalNewCases;
		totalDeaths = previousTotalDeaths + deaths;
		totalRecovered = previousTotalRecovered + recovered;
		totalUnderTreatment = totalCases - totalDeaths - totalRecovered;
		//Daily Comparative Report Process
		totalDeathsPercentage = (double)100 / totalCases * totalDeaths;
		totalRecoveredPercentage = (double)100 / totalCases * totalRecovered;
		underTreatmentPercentage = (double)100 / totalCases * totalUnderTreatment;
		//Calculate Difference Process
		totalCasesDifference = totalCases - totalPreviousCases;
		deathPercentageDifference = totalDeathsPercentage - previousDaytotalDeathsPercentage;
		totalRecoveredPerecentageDifference = totalRecoveredPercentage - previousTotalRecoveredPercentage;




		switch (choice)
		{
		case 1:

			printf("\nDAY %d%26.sDAILY SUMMARY REPORT \n", daycount, NULL);
			printf("+----------------------+-------------++--------+-----------+------------+\n");
			printf("|%14.sToday's%1.s|%1.sTotal%7.s||%1.sTotal%2.s|%3.sTotal%3.s|%4.sUnder%3.s|\n", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			printf("|%14.sCases%3.s|%1.sCases%7.s||%1.sdeaths%1.s|%1.sRecovered%1.s|%2.streatment%1.s|\n", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			printf("+----------------------+-------------++--------+-----------+------------+\n");
			printf("|%1.slocal%12.1d%4.s|%13.s||%8.s|%11.s|%12.s|\n", NULL, localCases, NULL, NULL, NULL, NULL, NULL);
			printf("|%1.simported%9.1d%4.s|%13.s||%8.s|%11.s|%12.s|\n", NULL, importedCases, NULL, NULL, NULL, NULL, NULL);
			printf("|%1.s%16d%5.s|%7d%6.s||%5d%3.s|%6d%5.s|%7d%5.s|\n", NULL, totalNewCases, NULL, totalCases, NULL, totalDeaths, NULL, totalRecovered, NULL, totalUnderTreatment, NULL);
			printf("+-----------------------------------------------------------------------+\n");
			printf("%37.s||%5.1f%%%2.s|%8.1f%%%2.s|%8.1f%%%3.s|\n", NULL, totalDeathsPercentage, NULL, totalRecoveredPercentage, NULL, underTreatmentPercentage, NULL);
			printf("%37.s++---------------------------------+\n", NULL);
			printf("\033[1;31m");
			printf("------------------------ End of Day %d Reporting -------------------------\n", daycount);
			printf("\033[0m");
			//Update
			previousCases = totalNewCases;
			totalPreviousCases = totalCases;
			previousTotalDeaths = totalDeaths;
			previousTotalRecovered = totalRecovered;
			previousDaytotalDeathsPercentage = totalDeathsPercentage;
			previousTotalRecoveredPercentage = totalRecoveredPercentage;
			daycount++;
			previousDaycount++;
			rewind(stdin);
			break;

		case 2:

			printf("\n%26.sDAILY COMPARATIVE REPORT \n", NULL);
			printf("%28.s+------------+------------++------------+\n", NULL);
			printf("%28.s|%2.sYesterday |%4.sToday%3.s|| DIFFERENCE |\n", NULL, NULL, NULL, NULL);
			printf("%28.s|%2.sDay %3.d %2.s|%4.sDay %d %2.s||%12.s|\n", NULL, NULL, previousDaycount, NULL, NULL, daycount, NULL, NULL);
			printf("+---------------------------+------------+------------++------------+\n");
			printf("|%2.sNew Cases%16.s|%9.1d%3.s|%7.1d%5.s||%2.s[%+5.1d]%3.s|\n", NULL, NULL, previousCases, NULL, totalNewCases, NULL, NULL, casesGap, NULL);
			printf("+---------------------------+------------+------------++------------+\n");
			printf("|%2.sTOTAL Cases%14.s|%9.1d%3.s|%7.1d%5.s||%2.s[%+5.1d]%3.s|\n", NULL, NULL, totalPreviousCases, NULL, totalCases, NULL, NULL, totalCasesDifference, NULL);
			printf("+---------------------------+------------+------------++------------+\n");
			printf("|%2.sDeath Rate%15.s|%9.1f%%%2.s|%7.1f%%%4.s||%2.s[%+5.1f%%]%2.s|\n", NULL, NULL, previousDaytotalDeathsPercentage, NULL, totalDeathsPercentage, NULL, NULL, deathPercentageDifference, NULL);
			printf("+---------------------------+------------+------------++------------+\n");
			printf("|%2.sRecovery Rate%12.s|%9.1f%%%2.s|%7.1f%%%4.s||%2.s[%+5.1f%%]%2.s|\n", NULL, NULL, previousTotalRecoveredPercentage, NULL, totalRecoveredPercentage, NULL, NULL, totalRecoveredPerecentageDifference, NULL);
			printf("+---------------------------+------------+------------++------------+\n");
			printf("\033[1;31m");
			printf("------------------------ End of Day  %d Reporting ------------------------\n", daycount);
			printf("\033[0m");
			//Update
			previousCases = totalNewCases;
			totalPreviousCases = totalCases;
			previousTotalDeaths = totalDeaths;
			previousTotalRecovered = totalRecovered;
			previousDaytotalDeathsPercentage = totalDeathsPercentage;
			previousTotalRecoveredPercentage = totalRecoveredPercentage;
			daycount++;
			previousDaycount++;
			rewind(stdin);
			break;

		default:
			printf("\n\nPLEASE ENTER VALID INPUT ONLY!!!!\n\n");
			rewind(stdin);
			continue;
		}
		//Validation
		while (choice < 1 || choice >2) {
			printf("\n1 - Daily Summary Report,%9.s2 - Daily Comparative Report\n", NULL);
			printf("What type of Report would you like to view (Choose 1 or 2)? > ");
			scanf("%d", &choice);
		}

		printf("Do you want to continue ?\n Enter any key to continue(N = stop): ");//Selection to stop the program
		scanf("%c", &selection);
		selection = toupper(selection);//Change every small letter from selection to capital letter
		//Calculate Highest Cases and Lowest Cases occuring on which day
		if (totalNewCases > highestCase) {
			highestCase = totalNewCases;
			highestCaseDay = daycount;
		}
		if (totalNewCases < lowestCase) {
			lowestCase = totalNewCases;
			lowestCaseDay = daycount;
		}


	} while (selection != 'N');

	printf("%11.sTOTAL Days recorded%7.s= %d days(Day 1 to Day %d)\n", NULL, NULL, daycount - 1, daycount - 1);   //Display Total Days Recorded
	printf("%11.sHIGHEST number of cases%3.s= %d, occurring on Day %d \n", NULL, NULL, highestCase, highestCaseDay - 1); //Display Highest number of cases and occuring on which day
	printf("%11.sLOWEST number of cases%4.s= %d, occurring on Day %d\n", NULL, NULL, lowestCase, lowestCaseDay - 1);//Display Lowest number of cases and occuring on which day
	printf("\n %10.sTHANK YOU FOR USING CCTP Covid-19 Tracking System!!\n", NULL);


}

