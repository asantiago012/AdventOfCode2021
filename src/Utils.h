#pragma once
#ifndef _UTILS_H
#define _UTILS_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>

using namespace std;

typedef struct puzzle_2_data_s {
	char* action;
	int value;
}puzzle_2_data_t;

typedef struct puzzle_4_data_s {
	int** board;
	int** marked;

	int cols;
	int rows;

	int num_chars_board;

	int already_won;
}puzzle_4_data_t;

typedef struct puzzle_5_data_s {
    int x0;
    int y0;
    int x1;
    int y1;
}puzzle_5_data_t;

extern char *read_file(const char* path, const char* filename, int* num_lines);
extern int *parse_buffer_numbers(const char *buffer, size_t size);
extern char** parse_buffer_strings(const char* buffer, size_t num_lines);
extern int* parse_line_csv_numbers(const char* buffer, int* num_numbers);
extern int** parse_matrix_numbers(const char* buffer, int* rows, int* cols, int* num_chars_matrix);

//PUZZLE 1
extern void how_many_increase_values_are(int* buffer, size_t size, int* increases, int* decreases, int* not_variant);
extern void how_many_increase_values_are_by_window(int* buffer, size_t size, int window_size, int* increases, int* decreases, int* not_variant);

//PUZZLE 2
extern puzzle_2_data_t* parse_buffer_puzzle_2_data(const char* buffer, size_t num_lines);
extern void calculate_position_at_end(puzzle_2_data_t* data, size_t num_lines, int* depth, int* length);
extern void calculate_position_at_end_with_aim(puzzle_2_data_t* data, size_t num_lines, int* depth, int* length, int* aim);

//PUZZLE 3
extern void calculate_gamma_epsilon_ratios(char** diagnosis_values, size_t num_lines, uint32_t* gamma, uint32_t* epsilon);
extern void calculate_oxygen_co2_rating(char** diagnosis_values, size_t num_lines, uint32_t* oxygen, uint32_t* c02);

//PUZZLE 4
extern puzzle_4_data_t* get_boards_from_string(const char* boards_lines, int* rows, int* cols, int* num_boards);
extern void get_winner_board(int* bingo_numbers, int num_bingo_numbers, puzzle_4_data_t* boards_info, int num_boards_info);
extern void get_loser_board(int* bingo_numbers, int num_bingo_numbers, puzzle_4_data_t* boards_info, int num_boards_info);

//PUZZLE 5
extern puzzle_5_data_t* get_hydrothermal_coordinates_from_string(char ** values_lines, int num_lines, int *rows, int *cols);
extern void draw_thermal_map(puzzle_5_data_t* thermal_info, int num_values, int rows, int cols, int diagonals_off);

//PUZZLE 6
extern void calculate_lanternfish_evolution(int *lanternfish_info, int num_initial_lanternfish, int num_days);
extern void calculate_lanternfish_evolution_states(int *lanternfish_info, int num_initial_lanternfish, int num_days);

//PUZZLE 7
extern void calculate_optimal_crabs_position(int *crabs_positions, int num_crabs);
extern void calculate_optimal_crabs_position_extra(int *crabs_positions, int num_crabs);

#endif // _UTILS_H