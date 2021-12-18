// AdventOfCode2021_cmake.cpp: define el punto de entrada de la aplicación.
//

#include "AdventOfCode2021_cmake.h"



void puzzle_1() {
    int num_lines_input1 = 0;
    char* input1 = read_file(AOC2021_INPUT_PATH, "input1", &num_lines_input1);
    int* depth_values = parse_buffer_numbers(input1, num_lines_input1);

    int increases = 0, decreases = 0, not_variant = 0;
    how_many_increase_values_are(depth_values, num_lines_input1, &increases, &decreases, &not_variant);
    printf("PUZZLE 1-1 Result: \nINCREASES: %d \nDECREASES: %d \nNOT_VARIANT: %d\n", increases, decreases, not_variant);

    how_many_increase_values_are_by_window(depth_values, num_lines_input1, 3, &increases, &decreases, &not_variant);
    printf("PUZZLE 1-2 Result: \nINCREASES: %d \nDECREASES: %d \nNOT_VARIANT: %d\n", increases, decreases, not_variant);

    free(input1);
    free(depth_values);
}

void puzzle_2() {
    int num_lines_input2 = 0;
    char* input2 = read_file(AOC2021_INPUT_PATH, "input2", &num_lines_input2);
    puzzle_2_data_t* action_values = parse_buffer_puzzle_2_data(input2, num_lines_input2);

    int depth = 0, length = 0;
    calculate_position_at_end(action_values, num_lines_input2, &depth, &length);
    printf("PUZZLE 2-1 Result: \nDEPTH: %d \nLENGTH: %d \nPRODUCT: %d\n", depth, length, depth * length);

    int aim = 0;
    calculate_position_at_end_with_aim(action_values, num_lines_input2, &depth, &length, &aim);
    printf("PUZZLE 2-2 Result: \nDEPTH: %d \nLENGTH: %d \nPRODUCT: %d\n", depth, length, depth * length);
}

void puzzle_3() {
    int num_lines_input3 = 0;
    char* input3 = read_file(AOC2021_INPUT_PATH, "input3", &num_lines_input3);
    char** diagnosis_values = parse_buffer_strings(input3, num_lines_input3);

    uint32_t gamma_rate = 0, epsilon_rate = 0;
    calculate_gamma_epsilon_ratios(diagnosis_values, num_lines_input3, &gamma_rate, &epsilon_rate);
    printf("PUZZLE 3-1 Result: \nGAMMA: %d \nEPSILON: %d \nPOWER: %d\n", gamma_rate, epsilon_rate, gamma_rate * epsilon_rate);

    uint32_t oxygen = 0, c02 = 0;
    calculate_oxygen_co2_rating(diagnosis_values, num_lines_input3, &oxygen, &c02);
    printf("PUZZLE 3-2 Result: \nO2: %d \nC02: %d \nLifeSupportRating: %d\n", oxygen, c02, oxygen * c02);


    free(input3);
    for (int idx = 0; idx < num_lines_input3; idx++) {
        free(diagnosis_values[idx]);
        diagnosis_values[idx] = NULL;
    }
    free(diagnosis_values);
}

void puzzle_4() {
    int num_lines_input4 = 0;
    char* input4 = read_file(AOC2021_INPUT_PATH, "input4", &num_lines_input4);
    char** bingo_values = parse_buffer_strings(input4, num_lines_input4);

    char* first_line = strtok_s(input4, "\n", &input4);
    char* boards_lines = input4 + 1;

    int num_numbers = 0, rows = 0, cols = 0, num_chars_board = 0, num_boards = 0;
    int* bingo_numbers = parse_line_csv_numbers(first_line, &num_numbers);
    puzzle_4_data_t* boards_info_to_win = get_boards_from_string(boards_lines, &rows, &cols, &num_boards);
    get_winner_board(bingo_numbers, num_numbers, boards_info_to_win, num_boards);
    puzzle_4_data_t* boards_info_to_lose = get_boards_from_string(boards_lines, &rows, &cols, &num_boards);
    get_loser_board(bingo_numbers, num_numbers, boards_info_to_lose, num_boards);

    printf("PUZZLE 4-1 & 4-2 Result: \nROWS: %d \nCOLS: %d \nNUM_BOARDS: %d\n", rows, cols, num_boards);




    free(input4);
    for (int idx = 0; idx < num_lines_input4; idx++) {
        free(bingo_values[idx]);
        bingo_values[idx] = NULL;
    }
    free(bingo_values);
    free(bingo_numbers);
    /*for (int idx = 0; idx < rows; idx++) {
        free(boards[idx]);
        boards[idx] = NULL;
    }
    free(boards);*/
    free(boards_info_to_win);
    free(boards_info_to_lose);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "ERROR: not puzzle number inserted... \n";
        return EXIT_FAILURE;
    }

    std::cout << "Advent Of Code 2021!\n";
    std::cout << "Executing puzzle number " << argv[1] << "\n";

    int puzzle_number = atoi(argv[1]);

    switch (puzzle_number)
    {
    case 1:
        puzzle_1();
        break;
    case 2:
        puzzle_2();
        break;
    case 3:
        puzzle_3();
        break;
    case 4:
        puzzle_4();
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}
