
#include "Utils.h"

#define PUZZLE2_FORDWARD "forward"
#define PUZZLE2_INCREASE_DEPTH "down"
#define PUZZLE2_DECREASE_DEPTH "up"
#define PUZZLE2_INCREASE_AIM "down"
#define PUZZLE2_DECREASE_AIM "up"

char *read_file(const char* path, const char* filename, int *num_lines) {
	FILE *fp = NULL;
	char *file_buffer = NULL;
	char *line_buffer = NULL;
	size_t file_tam = 0;
	char *filepath = NULL;
	int ret = -1;

	(*num_lines) = 0;
	
	filepath = (char*)calloc(strlen(path) + strlen(filename) + 1, sizeof(char));
	if (!filepath) {
		return NULL;
	}

	sprintf(filepath, "%s/", path);
	strcat(filepath, filename);

	fp = fopen(filepath, "r");
	if (fp == NULL) {
		goto err;
	}

	fseek(fp, 0, SEEK_END);
	file_tam = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	file_buffer = (char*)calloc(file_tam+1, sizeof(char));
	if (!file_buffer) {
		goto err;
	}

	line_buffer = (char*)calloc(1024 + 1, sizeof(char));
	fgets(line_buffer, 1024, fp);

	while (!feof(fp)) {
		(*num_lines)++;
		strcat(file_buffer, line_buffer);

		fgets(line_buffer, 1024, fp);
	}

	ret = 0;

err:
	if (fp) {
		fclose(fp);
	}
	free(line_buffer);

	if (ret) {
		free(file_buffer);
		file_buffer = NULL;
	}
	return file_buffer;
}

int *parse_buffer_numbers(const char* buffer, size_t num_lines) {
	
	int *numbers_buffer = (int*)calloc(num_lines, sizeof(int));
	char *p = (char*)buffer, *c = NULL;
	int idx = 0;

	c = strtok_r(p, "\n", &p);

	while (c) {
		numbers_buffer[idx] = atoi(c);
		idx++;
		c = strtok_r(p, "\n", &p);
	}


	return numbers_buffer;
}

char** parse_buffer_strings(const char* buffer, size_t num_lines) {

	char** strings_buffer = (char**)calloc(num_lines, sizeof(char*));

	char* p_buf = strdup(buffer);
	char* p = (char*)p_buf, * c = NULL;
	int idx = 0;

	c = strtok_r(p, "\n", &p);

	while (c) {
		strings_buffer[idx] = strdup(c);
		idx++;
		c = strtok_r(p, "\n", &p);
	}

	free(p_buf);

	return strings_buffer;
}

int* parse_line_csv_numbers(const char* buffer, int *num_numbers) {

	char* p_buf = strdup(buffer);
	(*num_numbers) = 0;

	int num_commas = 0;
	for (int idx_char = 0; idx_char < strlen(p_buf); idx_char++) {
		if (p_buf[idx_char] == ',') {
			num_commas++;
		}
	}

	int* numbers_buffer = (int*)calloc(num_commas+1, sizeof(int));
	char* p = (char*)p_buf, * c = NULL;
	int idx = 0;

	c = strtok_r(p, ",", &p);

	while (c) {
		numbers_buffer[idx] = atoi(c);
		(*num_numbers)++;
		idx++;
		c = strtok_r(p, ",", &p);
	}

	free(p_buf);

	return numbers_buffer;
}

int** parse_matrix_numbers(const char* buffer, int *rows, int *cols, int *num_chars_matrix) {

	char* p_buf = strdup(buffer);
	(*rows) = 0;
	(*cols) = 0;
	(*num_chars_matrix) = 0;

	int num_blanks = 0;
	//cannot be a blank on first char
	for (int idx_char = 1; idx_char < strlen(p_buf) - 1; idx_char++) {
		if (p_buf[idx_char] == '\n') {
			break;
		}
		if (p_buf[idx_char] == ' ' && p_buf[idx_char+1] != ' ') {
			num_blanks++;
		}
	}

	int** numbers_buffer = (int**)calloc(num_blanks+1, sizeof(int*));
	for (int idx = 0; idx < num_blanks + 1; idx++) {
		numbers_buffer[idx] = (int*)calloc(num_blanks + 1, sizeof(int));
	}

	(*rows) = num_blanks + 1;
	(*cols) = num_blanks + 1;

	char* p = (char*)p_buf, * c = NULL, *c_in = NULL;
	int idx_row = 0, idx_col = 0;

	for (idx_row = 0; idx_row < num_blanks + 1; idx_row++) {
		c = strtok_r(p, "\n", &p);
		(*num_chars_matrix) += strlen(c) + 1;

		for (idx_col = 0; idx_col < num_blanks; idx_col++) {
			c_in = strtok_r(c, " ", &c);
			numbers_buffer[idx_row][idx_col] = atoi(c_in);
		}
		c_in = strtok_r(c, "\n", &c);
		numbers_buffer[idx_row][num_blanks] = atoi(c_in);

	}


	free(p_buf);


	return numbers_buffer;
}

//PUZZLE 1
void how_many_increase_values_are(int* buffer, size_t size, int *increases, int *decreases, int *not_variant) {

	(*increases) = 0;
	(*decreases) = 0;
	(*not_variant) = 0;

	for (int idx = 1; idx < size; idx++) {

		if (buffer[idx] > buffer[idx-1]) {
			(*increases)++;
		}
		else {
			if (buffer[idx] < buffer[idx - 1]) {
				(*decreases)++;
			}
			else {
				(*not_variant)++;
			}
		}
	}

}
void how_many_increase_values_are_by_window(int* buffer, size_t size, int window_size, int* increases, int* decreases, int* not_variant) {

	(*increases) = 0;
	(*decreases) = 0;
	(*not_variant) = 0;

	int value_actual_window = 0, value_next_window = 0;

	for (int idx = 0; idx < size - window_size; idx++) {
		value_actual_window = 0;
		value_next_window = 0;

		for (int idx_window = idx; idx_window < idx + window_size && idx_window < size - window_size; idx_window++) {

			value_actual_window += buffer[idx_window];
			value_next_window += buffer[idx_window + 1];

		}

		if (value_next_window > value_actual_window) {
			(*increases)++;
		}
		else {
			if (value_next_window < value_actual_window) {
				(*decreases)++;
			}
			else {
				(*not_variant)++;
			}
		}
	}

}

//PUZZLE 2
puzzle_2_data_t* parse_buffer_puzzle_2_data(const char* buffer, size_t num_lines) {
	puzzle_2_data_t* struct_buffer = (puzzle_2_data_t*)calloc(num_lines, sizeof(puzzle_2_data_t));
	char* p = (char*)buffer, * c = NULL, *sub_c = NULL;
	int idx = 0, ret = -1;

	c = strtok_r(p, "\n", &p);

	while (c) {
		sub_c = strtok_r(c, " ", &c);
		struct_buffer[idx].action = strdup(sub_c);

		sub_c = strtok_r(c, "\n", &c);
		struct_buffer[idx].value = atoi(sub_c);
		idx++;
		c = strtok_r(p, "\n", &p);
	}

	ret = 0;
err:

	if (ret) {
		for (int idx = 0; idx < num_lines; idx++) {
			free(struct_buffer[idx].action);
		}
		free(struct_buffer);
		struct_buffer = NULL;
	}
	return struct_buffer;
}
void calculate_position_at_end(puzzle_2_data_t* data, size_t num_lines, int *depth, int *length) {
	(*depth) = 0;
	(*length) = 0;

	for (int idx = 0; idx < num_lines; idx++) {
		if (strcmp(data[idx].action, PUZZLE2_FORDWARD) == 0) {
			(*length) += data[idx].value;
		}
		else if (strcmp(data[idx].action, PUZZLE2_INCREASE_DEPTH) == 0) {
			(*depth) += data[idx].value;
		}
		else if (strcmp(data[idx].action, PUZZLE2_DECREASE_DEPTH) == 0) {
			(*depth) -= data[idx].value;
		}
		else {
			printf("PUZZLE2 ACTION NOT VALID: %s\n", data[idx].action);
		}
	}


}
void calculate_position_at_end_with_aim(puzzle_2_data_t* data, size_t num_lines, int* depth, int* length, int* aim) {
	(*depth) = 0;
	(*length) = 0;
	(*aim) = 0;

	for (int idx = 0; idx < num_lines; idx++) {
		if (strcmp(data[idx].action, PUZZLE2_FORDWARD) == 0) {
			(*length) += data[idx].value;
			(*depth) += (*aim) * data[idx].value;
		}
		else if (strcmp(data[idx].action, PUZZLE2_INCREASE_AIM) == 0) {
			(*aim) += data[idx].value;
		}
		else if (strcmp(data[idx].action, PUZZLE2_DECREASE_AIM) == 0) {
			(*aim) -= data[idx].value;
		}
		else {
			printf("PUZZLE2 ACTION NOT VALID: %s\n", data[idx].action);
		}
	}


}

//PUZZLE 3
void calculate_gamma_epsilon_ratios(char** diagnosis_values, size_t num_lines, uint32_t* gamma, uint32_t* epsilon) {
	int idx = 0, idx_char = 0;
	uint32_t lenght_string = 0, max_length_string = 0;
	uint32_t* mask_gamma_ones, * mask_epsilon_ones;

	(*gamma) = 0;
	(*epsilon) = 0;

	for (idx = 0; idx < num_lines; idx++) {
		if (strlen(diagnosis_values[idx]) > max_length_string) {
			max_length_string = strlen(diagnosis_values[idx]);
		}
	}

	mask_gamma_ones = (uint32_t*)calloc(max_length_string, sizeof(uint32_t));
	mask_epsilon_ones = (uint32_t*)calloc(max_length_string, sizeof(uint32_t));

	for (idx = 0; idx < num_lines; idx++) {
		lenght_string = strlen(diagnosis_values[idx]);

		for (idx_char = 0; idx_char < lenght_string; idx_char++) {
			if (diagnosis_values[idx][idx_char] == '1') {
				mask_gamma_ones[idx_char]++;
			}
		}
	}

	for (idx_char = 0; idx_char < max_length_string; idx_char++) {
		if (mask_gamma_ones[idx_char] > num_lines / 2) {
			(*gamma) |= 1 << (max_length_string-idx_char-1);
		}
		else {
			(*epsilon) |= 1 << (max_length_string - idx_char - 1);
		}
	}

	free(mask_gamma_ones);
	free(mask_epsilon_ones);
}
void calculate_oxygen_co2_rating(char** diagnosis_values, size_t num_lines, uint32_t* oxygen, uint32_t* c02) {
	int idx = 0, idx_char = 0, idx_char_output = 0;
	uint32_t lenght_string = 0, max_length_string = 0;
	uint8_t* valid_values_oxygen = NULL, * valid_values_c02 = NULL;

	(*oxygen) = 0;
	(*c02) = 0;

	for (idx = 0; idx < num_lines; idx++) {
		if (strlen(diagnosis_values[idx]) > max_length_string) {
			max_length_string = strlen(diagnosis_values[idx]);
		}
	}

	valid_values_oxygen = (uint8_t*)malloc(num_lines * sizeof(uint8_t));
	valid_values_c02 = (uint8_t*)malloc(num_lines * sizeof(uint8_t));
	memset(valid_values_oxygen, 1, num_lines);
	memset(valid_values_c02, 1, num_lines);


	int num_lines_iter_oxygen = num_lines, num_lines_iter_co2 = num_lines;
	//Assuming all numbers have same max_length
	for (idx_char = 0; idx_char < max_length_string; idx_char++) {

		char c_gamma = '0';
		char c_epsilon = '0';
		int ones_oxygen = 0, ones_co2 = 0;

		for (idx = 0; idx < num_lines; idx++) {

			if (diagnosis_values[idx][idx_char] == '1' && 
				valid_values_oxygen[idx] == 1) {
				ones_oxygen++;
			}

			if (diagnosis_values[idx][idx_char] == '1' &&
				valid_values_c02[idx] == 1) {
				ones_co2++;
			}
		}

		//printf("Oxygen ones [%d] -> threshold [%d/2]\n", ones_oxygen, num_lines_iter_oxygen);
		//printf("CO2    ones [%d] -> threshold [%d/2]\n", ones_co2, num_lines_iter_co2);

		if ((float)ones_oxygen >= (float)num_lines_iter_oxygen / 2) {
			//more 1 than 0, or same
			c_gamma = '1';
		}
		else {
			//more 0 than 1
			c_gamma = '0';
		}

		if ((float)ones_co2 >= (float)num_lines_iter_co2 / 2) {
			//more 1 than 0, or same
			c_epsilon = '0';
		}
		else {
			//more 0 than 1
			c_epsilon = '1';

		}

		/*printf("------------------------- [%d] ------------------------- \n", idx_char);
		printf("Oxygen valid values idx_char[%d] -> most common value is %c\n", idx_char, c_gamma);
		for (idx = 0; idx < num_lines; idx++) {
			if (valid_values_oxygen[idx] == 1) {
				printf("\t%s\n", diagnosis_values[idx]);
				num_lines_iter_oxygen++;
			}
		}
		printf("C02 valid value: idx_char[%d] -> less common value is %c\n", idx_char, c_epsilon);
		for (idx = 0; idx < num_lines; idx++) {
			if (valid_values_c02[idx] == 1) {
				printf("\t%s\n", diagnosis_values[idx]);
				num_lines_iter_co2++;
			}
		}*/


		for (idx = 0; idx < num_lines; idx++) {

			if (diagnosis_values[idx][idx_char] != c_gamma && 
				num_lines_iter_oxygen > 1) {
				valid_values_oxygen[idx] = 0;
			}

			if (diagnosis_values[idx][idx_char] != c_epsilon &&
				num_lines_iter_co2 > 1) {
				valid_values_c02[idx] = 0;
			}
		}

		num_lines_iter_oxygen = 0;
		num_lines_iter_co2 = 0;
		//printf("------------------------- [%d] modif ------------------------- \n", idx_char);
		//printf("Oxygen valid values idx_char[%d] -> most common value is %c\n", idx_char, c_gamma);
		for (idx = 0; idx < num_lines; idx++) {
			if (valid_values_oxygen[idx] == 1) {
				//printf("\t%s\n", diagnosis_values[idx]);
				num_lines_iter_oxygen++;
			}
		}
		//printf("C02 valid value: idx_char[%d] -> less common value is %c\n", idx_char, c_epsilon);
		for (idx = 0; idx < num_lines; idx++) {
			if (valid_values_c02[idx] == 1) {
				//printf("\t%s\n", diagnosis_values[idx]);
				num_lines_iter_co2++;
			}
		}

		if (num_lines_iter_oxygen == 1) {
			for (idx = 0; idx < num_lines; idx++) {
				if (valid_values_oxygen[idx] == 0) {
					continue;
				}
				for (idx_char_output = 0; idx_char_output < max_length_string; idx_char_output++) {
					if (diagnosis_values[idx][idx_char_output] == '1') {
						(*oxygen) |= 1 << (max_length_string - idx_char_output - 1);
					}
				}
			}
		}

		if (num_lines_iter_co2 == 1) {
			for (idx = 0; idx < num_lines; idx++) {
				if (valid_values_c02[idx] == 0) {
					continue;
				}
				for (idx_char_output = 0; idx_char_output < max_length_string; idx_char_output++) {
					if (diagnosis_values[idx][idx_char_output] == '1') {
						(*c02) |= 1 << (max_length_string - idx_char_output - 1);
					}
				}
			}
		
		}

		int debug_here = 0;
	}


	free(valid_values_oxygen);
	free(valid_values_c02);
}

//PUZZLE 4
puzzle_4_data_t* get_boards_from_string(const char* boards_lines, int* rows, int* cols, int *num_boards) {
	
	char* p_buf = strdup(boards_lines);
	(*num_boards) = 0;
	(*rows) = 0;
	(*cols) = 0;

	char* p_buf_to_free = p_buf;

	for (int idx = 0; idx < strlen(p_buf); idx++) {
		if (p_buf[idx] == '\n' && p_buf[idx + 1] == '\n' || 
			p_buf[idx] == '\n' && p_buf[idx + 1] == '\0') {
			(*num_boards)++;
		}
	}

	puzzle_4_data_t* boards_info = (puzzle_4_data_t*)calloc((*num_boards), sizeof(puzzle_4_data_t));


	for (int idx = 0; idx < (*num_boards); idx++) {
		while (p_buf[0] == '\n') {
			p_buf++;
		}
		boards_info[idx].board = parse_matrix_numbers(	p_buf, 
														&boards_info[idx].rows, 
														&boards_info[idx].cols,
														&boards_info[idx].num_chars_board);
		boards_info[idx].marked = (int**)calloc(boards_info[idx].rows, sizeof(int*));
		for (int idx_mark = 0; idx_mark < boards_info[idx].rows; idx_mark++) {
			boards_info[idx].marked[idx_mark] = (int*)calloc(boards_info[idx].cols, sizeof(int));
		}

		p_buf += boards_info[idx].num_chars_board;
	}



	free(p_buf_to_free);


	return boards_info;
}
int has_marked_row(puzzle_4_data_t board) {

	for (int idx_row = 0; idx_row < board.rows; idx_row++) {
		int marked_elements = 0;

		for (int idx_col = 0; idx_col < board.cols; idx_col++) {
			if (board.marked[idx_row][idx_col] == 1) {
				marked_elements++;
			}
		}

		if (marked_elements == board.cols) {
			printf("ROW in row %d ---> ", idx_row);
			for (int idx_col = 0; idx_col < board.cols; idx_col++) {
				printf("  %d", board.board[idx_row][idx_col]);
			}
			printf("\n");
			return 1;
		}
	}

	return 0;
}
int has_marked_col(puzzle_4_data_t board) {
	for (int idx_col = 0; idx_col < board.cols; idx_col++) {
		int marked_elements = 0;

		for (int idx_row = 0; idx_row < board.rows; idx_row++) {
			if (board.marked[idx_row][idx_col] == 1) {
				marked_elements++;
			}
		}

		if (marked_elements == board.rows) {
			printf("COL in col %d ---> ", idx_col);
			for (int idx_row = 0; idx_row < board.rows; idx_row++) {
				printf("  %d\n", board.board[idx_row][idx_col]);
			}
			printf("\n");
			return 1;
		}
	}

	return 0;
}
void calculate_score(puzzle_4_data_t board, int actual_value) {
	int res = 0, sum = 0;
	for (int idx_row = 0; idx_row < board.rows; idx_row++) {
		for (int idx_col = 0; idx_col < board.cols; idx_col++) {
			if (board.marked[idx_row][idx_col] == 0) {
				sum += board.board[idx_row][idx_col];
			}
		}
	}

	res = sum*actual_value;
	printf("SCORE: unmarked-sum(%d) last_number(%d) product(%d)\n", sum, actual_value, res);

}
void get_winner_board(int* bingo_numbers, int num_bingo_numbers, puzzle_4_data_t* boards_info, int num_boards_info) {

	int found_winner = 0;

	for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
		//for each board
		printf("\nBOARD %d\n", idx_board);
		for (int idx_row = 0; idx_row < boards_info[idx_board].rows; idx_row++) {
			//for each row
			for (int idx_col = 0; idx_col < boards_info[idx_board].cols; idx_col++) {
				//for each col
				printf("%d ", boards_info[idx_board].board[idx_row][idx_col]);
			}
			printf("\n");
		}
	}

	for (int idx_bingo = 0; idx_bingo < num_bingo_numbers; idx_bingo++) {
		//for each number
		for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
			//for each board
			for (int idx_row = 0; idx_row < boards_info[idx_board].rows; idx_row++) {
				//for each row
				for (int idx_col = 0; idx_col < boards_info[idx_board].cols; idx_col++) {
					//for each col
					if (boards_info[idx_board].board[idx_row][idx_col] == bingo_numbers[idx_bingo]) {
						printf("MARK: board(%d) row(%d) col(%d) value(%d)\n", idx_board, idx_row, idx_col, bingo_numbers[idx_bingo]);
						boards_info[idx_board].marked[idx_row][idx_col] = 1;
					}
				}
			}
		}

		for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
			//for each board
			if (has_marked_row(boards_info[idx_board]) == 1) {
				printf("Winner board is board number %d with a ROW with %d numbers in bingo\n", idx_board+1, idx_bingo+1);
				found_winner = 1;
				calculate_score(boards_info[idx_board], bingo_numbers[idx_bingo]);
				break;
			}
			if (has_marked_col(boards_info[idx_board]) == 1) {
				printf("Winner board is board number %d with a COL %d numbers in bingo\n", idx_board+1, idx_bingo+1);
				found_winner = 1;
				calculate_score(boards_info[idx_board], bingo_numbers[idx_bingo]);
				break;
			}
		}

		if (found_winner) {
			break;
		}
	}
}
void get_loser_board(int* bingo_numbers, int num_bingo_numbers, puzzle_4_data_t* boards_info, int num_boards_info) {

	int idx_last_board = 0, idx_last_number = 0;

	for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
		//for each board
		if (boards_info[idx_board].already_won == 1) {
			continue;
		}

		printf("\nBOARD %d\n", idx_board);
		for (int idx_row = 0; idx_row < boards_info[idx_board].rows; idx_row++) {
			//for each row
			for (int idx_col = 0; idx_col < boards_info[idx_board].cols; idx_col++) {
				//for each col
				printf("%d ", boards_info[idx_board].board[idx_row][idx_col]);
			}
			printf("\n");
		}
	}

	for (int idx_bingo = 0; idx_bingo < num_bingo_numbers; idx_bingo++) {
		//for each number
		for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
			//for each board
			if (boards_info[idx_board].already_won == 1) {
				continue;
			}

			for (int idx_row = 0; idx_row < boards_info[idx_board].rows; idx_row++) {
				//for each row
				for (int idx_col = 0; idx_col < boards_info[idx_board].cols; idx_col++) {
					//for each col
					if (boards_info[idx_board].board[idx_row][idx_col] == bingo_numbers[idx_bingo]) {
						printf("MARK: board(%d) row(%d) col(%d) value(%d)\n", idx_board, idx_row, idx_col, bingo_numbers[idx_bingo]);
						boards_info[idx_board].marked[idx_row][idx_col] = 1;
					}
				}
			}
		}

		for (int idx_board = 0; idx_board < num_boards_info; idx_board++) {
			//for each board
			if (boards_info[idx_board].already_won == 1) {
				continue;
			}

			if (has_marked_row(boards_info[idx_board]) == 1) {
				printf("Winner board is board number %d with a ROW with %d numbers in bingo\n", idx_board + 1, idx_bingo + 1);
				boards_info[idx_board].already_won = 1;
				calculate_score(boards_info[idx_board], bingo_numbers[idx_bingo]);
				idx_last_board = idx_board;
				idx_last_number = idx_bingo;
				continue;
			}

			if (has_marked_col(boards_info[idx_board]) == 1) {
				printf("Winner board is board number %d with a COL %d numbers in bingo\n", idx_board + 1, idx_bingo + 1);
				boards_info[idx_board].already_won = 1;
				calculate_score(boards_info[idx_board], bingo_numbers[idx_bingo]);
				idx_last_board = idx_board;
				idx_last_number = idx_bingo;
				continue;
			}
		}
	}

	printf("Last winner board is board number %d with %d numbers in bingo --> Last number (%d)\n", idx_last_board + 1, idx_last_number + 1, bingo_numbers[idx_last_number]);
	calculate_score(boards_info[idx_last_board], bingo_numbers[idx_last_number]);
	
}

//PUZZLE 5
puzzle_5_data_t* get_hydrothermal_coordinates_from_string(char ** values_lines, int num_lines, int *rows, int *cols){

    (*rows) = 0;
    (*cols) = 0;

    puzzle_5_data_t* hydrothermal_info = (puzzle_5_data_t*)calloc(num_lines, sizeof(puzzle_5_data_t));


    for (int idx = 0; idx < num_lines; idx++) {
        sscanf(values_lines[idx],
               "%d,%d -> %d,%d",
               &hydrothermal_info[idx].x0, &hydrothermal_info[idx].y0,
               &hydrothermal_info[idx].x1, &hydrothermal_info[idx].y1);

        if(hydrothermal_info[idx].x0 > (*cols)){
            (*cols) = hydrothermal_info[idx].x0;
        }
        if(hydrothermal_info[idx].x1 > (*cols)){
            (*cols) = hydrothermal_info[idx].x1;
        }

        if(hydrothermal_info[idx].y0 > (*rows)){
            (*rows) = hydrothermal_info[idx].y0;
        }
        if(hydrothermal_info[idx].y1 > (*rows)){
            (*rows) = hydrothermal_info[idx].y1;
        }

        puzzle_5_data_t hydro_info = hydrothermal_info[idx];

        int iii = 0;
    }

    return hydrothermal_info;
}
void draw_thermal_map(puzzle_5_data_t* thermal_info, int num_values, int rows, int cols, int diagonals_off){

    int ** thermal_map = (int**)calloc(rows, sizeof (int*));
    for(int idx = 0; idx < rows; idx++){
        thermal_map[idx] = (int*)calloc(cols, sizeof (int));
    }

    for(int idx = 0; idx < num_values; idx++){
        puzzle_5_data_t data = thermal_info[idx];

        if( diagonals_off == 1 &&
            data.x0 != data.x1 &&
            data.y0 != data.y1){
            continue;
        }

        int x0 = 0, y0 = 0, x1 = 0, y1 = 0;

        if(data.x0 > data.x1){
            x0 = data.x1;
            x1 = data.x0;
        }
        else{
            x0 = data.x0;
            x1 = data.x1;
        }

        if(data.y0 > data.y1){
            y0 = data.y1;
            y1 = data.y0;
        }
        else{
            y0 = data.y0;
            y1 = data.y1;
        }

        int inc_x = data.x1-data.x0;
        int inc_y = data.y1-data.y0;
        int inverted_diag = 0;
        int x = 0;

        if( diagonals_off == 0 && inc_x != 0 && inc_y != 0)  {
            //45º diagonals only

            if( (inc_x > 0 && inc_y > 0) || ((inc_x < 0 && inc_y < 0))){
                //Diagonal
                printf("Diagonal from (%d,%d) to (%d,%d)\n", data.x0, data.y0, data.x1, data.y1);

                x = x0;
            }
            else if ( (inc_x > 0 && inc_y < 0) || ((inc_x < 0 && inc_y > 0)))
            {
                //Inverted Diagonal
                printf("Inverted Diagonal from (%d,%d) to (%d,%d)\n", data.x0, data.y0, data.x1, data.y1);
                x = x1;
                inverted_diag = 1;
            }

            for (int y = y0; y <= y1; y++) {
                if (x > x1 && inverted_diag == 0) {
                    break;
                } else if (x < x0 && inverted_diag == 1) {
                    break;
                }
                thermal_map[y][x]++;
                inverted_diag == 1 ? x-- : x++;
            }
        }
        else {
            //Vertical & Horizontal lines
            for (int x = x0; x <= x1; x++) {
                for (int y = y0; y <= y1; y++) {
                    thermal_map[y][x]++;
                }
            }
        }

//        printf("-----------------------------------------\n");
//        printf("%d,%d -> %d,%d\n",data.x0, data.y0, data.x1, data.y1 );
//        for(int x = 0; x < rows; x++){
//            for(int y = 0; y < cols; y++){
//                thermal_map[x][y] != 0 ? printf("%d ", thermal_map[x][y]) : printf(". ");
//            }
//            printf("\n");
//        }
//        printf("-----------------------------------------\n");
    }


    printf("-----------------------------------------\n");
    diagonals_off == 1 ?  printf("Disabled diagonals\n") : printf("Enabled diagonals\n");
    int num_dangerous_points = 0;
    for(int x = 0; x < rows; x++){
        for(int y = 0; y < cols; y++){
            thermal_map[x][y] != 0 ? printf("%d ", thermal_map[x][y]) : printf(". ");
            if(thermal_map[x][y]>=2){
                num_dangerous_points++;
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    printf("DANGEROUS POINTS: %d\n", num_dangerous_points);



    for(int idx = 0; idx < rows; idx++){
        free(thermal_map[idx]);
    }
    free(thermal_map);
}