#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}
static char* get_O_name(result_t *resultArray, int speed){


	if(speed == 1){
	if(resultArray[0].faster_O_notation_t == O_one_t)
		return "T / one";
	else if(resultArray[0].faster_O_notation_t == O_n_t)
		return "T / n";
	else if(resultArray[0].faster_O_notation_t == O_n2_t)
		return "T / n^2";
	else if(resultArray[0].faster_O_notation_t == O_n3_t)
		return "T / n^3";
	else if(resultArray[0].faster_O_notation_t == O_logn_t)
		return "T / logn";
	else if(resultArray[0].faster_O_notation_t == O_nlogn_t)
		return "T / nlogn";
	}
	if(speed == 2){
		if(resultArray[0].slower_O_notation_t == O_one_t)
			return "T / one";
		else if(resultArray[0].slower_O_notation_t == O_n_t)
			return "T / n";
		else if(resultArray[0].slower_O_notation_t == O_n2_t)
			return "T / n^2";
		else if(resultArray[0].slower_O_notation_t == O_n3_t)
			return "T / n^3";
		else if(resultArray[0].slower_O_notation_t == O_logn_t)
			return "T / logn";
		else if(resultArray[0].slower_O_notation_t == O_nlogn_t)
			return "T / nlogn";
	}
	if(speed == 3){
		if(resultArray[0].big_O_notation_t == O_one_t)
			return "T / one";
		else if(resultArray[0].big_O_notation_t == O_n_t)
			return "T / n";
		else if(resultArray[0].big_O_notation_t == O_n2_t)
			return "T / n^2";
		else if(resultArray[0].big_O_notation_t == O_n3_t)
			return "T / n^3";
		else if(resultArray[0].big_O_notation_t == O_logn_t)
			return "T / logn";
		else if(resultArray[0].big_O_notation_t == O_nlogn_t)
			return "T / nlogn";
	} 
	
	return 0;
}

static void reset_result_array(result_t *resultArray){
	for(int i = 0; i < 6 ; i++){
		resultArray[i].size = 0;
		resultArray[i].time = 0;
		resultArray[i].big_O_notation_value = 0;
		resultArray[i].faster_O_notation_value = 0;
		resultArray[i].slower_O_notation_value = 0;
/* 		resultArray[i].faster_O_notation_t = NULL;
		resultArray[i].slower_O_notation_t = NULL;
		resultArray[i].big_O_notation_t = NULL; */

	}
}

static void display(result_t *resultArray){
	char s [] = "Array size";
	char t [] = "Time (s)"; 
	ui_line('*',3.1 * MENU_WIDTH);
	char *faster = get_O_name(resultArray,1);
	char *slower = get_O_name(resultArray,2);
	char *bigO = get_O_name(resultArray,3);
	printf("%-25s %-26s %-26s %-26s %-26s\n",s,t,faster,bigO,slower);
	ui_line('-',3.1 * MENU_WIDTH);
	for(int i = 0; i < RESULT_ROWS;i++){
		printf("|%-25d| %-25.10f| %-25.10f| %-25.10f| %-25.10f\n",resultArray[i].size,resultArray[i].time/BILLION,resultArray[i].faster_O_notation_value,resultArray[i].big_O_notation_value,resultArray[i].slower_O_notation_value);
	}
	ui_line('*',3.1 * MENU_WIDTH);
	reset_result_array(resultArray);
}

static void ui_menu()
{
	const char *options[] = {
        "Menu",
        "Exit\n",
        "Bubble sort best case",
        "Bubble sort worst case",
        "Bubble sort average case\n",
        "Insertion sort best case",
        "Insertion sort worst case",
        "Insertion sort average case\n",
        "Quick sort sort best case",
        "Quick sort worst case",
        "Quick sort average case\n",
        "Linear search best case",
        "Linear search worst case",
        "Linear search average case\n",
        "Binary search best case",
        "Binary search worst case",
        "Binary search average case",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
    system("clear");
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':	//Menue
			    system("clear");
				show_menu = true;
				break;

			case 'b':	//Exit
				running = false;
				break;

			case 'c':	//Bubble BC
				printf("\nBubblesort: best case\nCalculating... \n" );
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'd':	//Bubble WC
				printf("\nBubblesort: worst case\nCalculating... \n" );			
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'e':	//Bubble AC
				printf("\nBubblesort: avarage case\nCalculating... \n" );
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'f':	//Inster BC
				printf("\nInsertsort: best case\nCalculating... \n" );
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'g':	//Insert WC
				printf("\nInsertsort: worst case\nCalculating... \n" );
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'h':	//Insert AC
				printf("\nInsertsort: avarage case\nCalculating... \n" );
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				display(result);		
				break;
			case 'i':	//Quick BC
				printf("\nQuicksort: best case\nCalculating... \n" );
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'j':	//Quick WC
				printf("\nQuicksort: worst case\nCalculating... \n" );
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'k':	//Quick AC
				printf("\nQuicksort: avarage case\nCalculating... \n" );
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'l':	//Linear BC
				printf("\nLinear search: best case\nCalculating... \n" );
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'm':	//Linear WC
				printf("\nLinear search: worst case\nCalculating... \n" );
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'n':	//Linear AC
				printf("\nLinear search: avarage case\nCalculating... \n" );
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'o':	//Binary BC
				printf("\nBinary search: best case\nCalculating... \n" );
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'p':	//Binary WC
				printf("\nBinary search: worst case\nCalculating... \n" );
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				display(result);
				break;
			case 'q':	//Binary AC
				printf("\nBinary search: avarage case\nCalculating... \n" );
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				display(result);
				break;			
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
