// TableBlockRearranger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ReSharper disable CommentTypo
// ReSharper disable StringLiteralTypo
// ReSharper disable CppClangTidyPerformanceInefficientStringConcatenation
#include <iostream>
#include <stack>

using namespace std;

/// <summary>
/// Checks whether a string contains a specified character at least once within it.
///	This exists because the C++ "find" function does not work reliably.
/// </summary>
/// <param name="string_to_check"></param>
/// <param name="character_to_find"></param>
/// <returns></returns>
bool contains_character(string string_to_check, char character_to_find){
	for(unsigned int i = 0; i < string_to_check.length(); i++){
		if(string_to_check[i] == character_to_find){
			return true;
		}
	}

	return false;
}

/// <summary>
/// Returns a string printing the stack from bottom to top. Stack will end up in its original state.
/// </summary>
/// <param name="stack_to_convert"></param>
/// <returns></returns>
string put_stack_into_string(stack<char>* stack_to_convert){
	stack<char>* temporary_stack = new stack<char>();
	string resulting_string;

	while(!stack_to_convert->empty()){
		temporary_stack->push(stack_to_convert->top());
		stack_to_convert->pop();
	}

	while(!temporary_stack->empty()){
		resulting_string += temporary_stack->top();
		stack_to_convert->push(temporary_stack->top());
		temporary_stack->pop();
	}

	return resulting_string;
}

/// <summary>
/// Prints the current state to the console, with an extra message displayed before.
/// </summary>
/// <param name="location_1"></param>
/// <param name="location_2"></param>
/// <param name="location_3"></param>
/// <param name="extra_message"></param>
void print_current_state(stack<char>* location_1, stack<char>* location_2, stack<char>* location_3){
	cout << "\n\nLocation 1: ";
	cout << put_stack_into_string(location_1);

	cout << "\nLocation 2: ";
	cout << put_stack_into_string(location_2);

	cout << "\nLocation 3: ";
	cout << put_stack_into_string(location_3);

	cout << "\n";
}

/// <summary>
/// Moves a specified number of items from location_to_move_from to location_to_move_to.
///	Does not check if the number_of_items_to_move is invalid.
/// </summary>
/// <param name="location_to_move_from"></param>
/// <param name="location_to_move_to"></param>
/// <param name="number_of_items_to_move"></param>
/// <param name="move_from_name"></param>
/// <param name="move_to_name"></param>
void move_items_from_location_to_location(stack<char>* location_to_move_from, stack<char>* location_to_move_to, const unsigned int number_of_items_to_move, const string& move_from_name, const string& move_to_name){
	for(unsigned int i = 0; i < number_of_items_to_move; i++){
		cout << "\nMove \'" + string(1, location_to_move_from->top()) + "\' from " + move_from_name + " to " + move_to_name + ".";
		location_to_move_to->push(location_to_move_from->top());
		location_to_move_from->pop();
	}
}

/// <summary>
/// Uses an algorithm to complete the specified location using the data from location_to_pull_from and putting unused data into location_to_use_as_buffer.
///	Assumes location_to_complete is empty.
/// </summary>
/// <param name="location_to_complete"></param>
/// <param name="location_to_move_from"></param>
/// <param name="location_to_use_as_buffer"></param>
/// <param name="location_end"></param>
/// <param name="move_to_complete_name"></param>
/// <param name="move_from_name"></param>
/// <param name="move_to_buffer_name"></param>
void complete_location_from_location_using_location_as_buffer(stack<char>* location_to_complete, stack<char>* location_to_move_from, stack<char>* location_to_use_as_buffer, const string& location_end, const string& move_to_complete_name,
                                                              const string& move_from_name, const string& move_to_buffer_name){

	for(unsigned int i = 0; i < location_end.length(); i++){
		unsigned int number_of_items_put_into_buffer = 0;
		while(!location_to_move_from->empty()){
			if(location_to_move_from->top() == location_end[i]){
				cout << "\nMove \'" + string(1, location_to_move_from->top()) + "\' from " + move_from_name + " to " + move_to_complete_name + ".";
				location_to_complete->push(location_to_move_from->top());
			}
			else{
				cout << "\nMove \'" + string(1, location_to_move_from->top()) + "\' from " + move_from_name + " to " + move_to_buffer_name + ".";
				location_to_use_as_buffer->push(location_to_move_from->top());
				number_of_items_put_into_buffer++;
			}

			location_to_move_from->pop();
		}

		move_items_from_location_to_location(location_to_use_as_buffer, location_to_move_from, number_of_items_put_into_buffer, move_to_buffer_name, move_from_name); // Move the items back from buffer so buffer is reverted to original state.
	}
}

/// <summary>
/// Moves all items from both location_to_move_from and other_location_to_move_from (in that order).
/// </summary>
/// <param name="location_to_move_to"></param>
/// <param name="location_to_move_from"></param>
/// <param name="other_location_to_move_from"></param>
/// <param name="move_to_name"></param>
/// <param name="move_from_name"></param>
/// <param name="other_move_from_name"></param>
void move_all_to_location_from_other_locations(stack<char>* location_to_move_to, stack<char>* location_to_move_from,
                                               stack<char>* other_location_to_move_from, const string& move_to_name, const string& move_from_name, const string& other_move_from_name){
	while(!location_to_move_from->empty()){
		cout << "\nMove \'" + string(1, location_to_move_from->top()) + "\' from " + move_from_name + " to " + move_to_name + ".";
		location_to_move_to->push(location_to_move_from->top());
		location_to_move_from->pop();
	}

	while(!other_location_to_move_from->empty()){
		cout << "\nMove \'" + string(1, other_location_to_move_from->top()) + "\' from " + move_from_name + " to " + other_move_from_name + ".";
		location_to_move_to->push(other_location_to_move_from->top());
		other_location_to_move_from->pop();
	}
}

/// <summary>
/// Moves all items from location_to_move_from to location_to_move_to.
/// </summary>
/// <param name="location_to_move_from"></param>
/// <param name="location_to_move_to"></param>
/// <param name="move_from_name"></param>
/// <param name="move_to_name"></param>
void move_location_to_location(stack<char>* location_to_move_from, stack<char>* location_to_move_to, const string& move_from_name, const string& move_to_name){
	while(!location_to_move_from->empty()){
		cout << "\nMove \'" + string(1, location_to_move_from->top()) + "\' from " + move_from_name + " to " + move_to_name + ".";
		location_to_move_to->push(location_to_move_from->top());
		location_to_move_from->pop();
	}
}

/// <summary>
/// Asks the user for start and end inputs and executes the algorithm needed to make it happen.
/// </summary>
/// <returns></returns>
int main() // NOLINT(bugprone-exception-escape)
{
	while(true){
		// We are storing the starting strings in here.
		string location_1_start;
		string location_2_start;
		string location_3_start;

		cout <<
			"\n\nInput starting position of blocks bottom-to-top on location 1 as a string of up to 14 characters (a through n), no spaces or commas.\n";
		cout << "For example, \"adbcfeghikljmn\" (without the quotes).\n";
		cout << "Enter your input here (enter only \"0\" if empty): ";
		cin >> location_1_start;
		if(location_1_start == "0"){
			location_1_start = "";
		}

		cout << "\nInput starting position of blocks on location 2 (enter only \"0\" if empty): ";
		cin >> location_2_start;
		if(location_2_start == "0"){
			location_2_start = "";
		}

		cout << "\nInput starting position of blocks on location 3 (enter only \"0\" if empty): ";
		cin >> location_3_start;
		if(location_3_start == "0"){
			location_3_start = "";
		}

		// We are storing the ending strings in here.
		string location_1_end;
		string location_2_end;
		string location_3_end;

		cout << "\n\nNow we will enter the desired ending positions of the three locations. Same rules apply.";
		cout << "\nInput ending position of blocks on location 1 (enter only \"0\" if empty): ";
		cin >> location_1_end;
		if(location_1_end == "0"){
			location_1_end = "";
		}

		cout << "\nInput ending position of blocks on location 2 (enter only \"0\" if empty): ";
		cin >> location_2_end;
		if(location_2_end == "0"){
			location_2_end = "";
		}

		cout << "\nInput ending position of blocks on location 3 (enter only \"0\" if empty): ";
		cin >> location_3_end;
		if(location_3_end == "0"){
			location_3_end = "";
		}

		// Check if number of starting and ending elements are equal.
		if(location_1_end.length() + location_2_end.length() + location_3_end.length() != location_1_start.length() + location_2_start.length() + location_3_start.length()){
			cout << "\n\n-----------------------------ERROR------------------------------\n";
			cout << "The number of items at the start should be equal to the number of items at the end. Please try again.";

			continue;
		}

		// Check that every element at start is also in the ending locations, and vice versa.
		{
			string combined_start = location_1_start + location_2_start + location_3_start;
			string combined_ending = location_1_end + location_2_end + location_3_end;
			bool is_valid = true;
			for(unsigned int i = 0; i < combined_start.length() && is_valid; i++){
				if(!contains_character(combined_ending, combined_start[i])){
					cout << "\n\n-----------------------------ERROR------------------------------\n";
					cout << "Every item from the starting locations should also be present somewhere in the ending locations.\n";
					cout << "Currently, \'" + string(1, combined_start[i]) + "\' is present in the start state but not the end state. Please try again.";

					is_valid = false;
					break;
				}
			}
			for(unsigned int i = 0; i < combined_ending.length() && is_valid; i++){
				if(!contains_character(combined_start, combined_ending[i])){
					cout << "\n\n-----------------------------ERROR------------------------------\n";
					cout << "Every item from the ending locations should also be present somewhere in the starting locations.\n";
					cout << "Currently, \'" + string(1, combined_ending[i]) + "\' is present in the ending state but not the start state. Please try again.";

					is_valid = false;
					break;
				}
			}
			if(!is_valid){
				continue;
			}
		}

		// The current state of each location, as a stack data type (for pushing and popping)
		stack<char>* location_1 = new stack<char>();
		stack<char>* location_2 = new stack<char>();
		stack<char>* location_3 = new stack<char>();

		// Push string characters onto their respective stacks. Now we're set.
		for(unsigned int i = 0; i < location_1_start.length(); i++){
			location_1->push(location_1_start[i]);
		}
		for(unsigned int i = 0; i < location_2_start.length(); i++){
			location_2->push(location_2_start[i]);
		}
		for(unsigned int i = 0; i < location_3_start.length(); i++){
			location_3->push(location_3_start[i]);
		}

		// Perform algorithm
		// First we move everything from location 2 and location 3 to location 1. Locations 2 and 3 will be empty.
		cout << "\n\nFirst we move everything from location 2 and location 3 to location 1. Locations 2 and 3 will be empty.";
		move_all_to_location_from_other_locations(location_1, location_2, location_3, "Location 1", "Location 2", "Location 3");
		print_current_state(location_1, location_2, location_3);

		// Now we "complete" location 3 by popping items from location 1 (which has all the items). Invalid items are temporarily held in location 2. At the end, buffer is moved back to location 1, so location 2 will still be empty at the end.
		cout << "\nNow we \"complete\" location 3 by popping items from location 1 (which has all the items). Invalid items are temporarily held in location 2. At the end, buffer is moved back to location 1, so location 2 will still be empty at the end.";
		complete_location_from_location_using_location_as_buffer(location_3, location_1, location_2, location_3_end, "Location 3", "Location 1", "Location 2");
		print_current_state(location_1, location_2, location_3);

		// Now we complete location 2 from location 1 similar to above, but we use location 3 as a buffer. It'll just stack on top of items already in location 3, but they'll be put back in location 1 at the end.
		cout << "\nNow we complete location 2 from location 1 similar to above, but we use location 3 as a buffer. It'll just stack on top of items already in location 3, but they'll be put back in location 1 at the end.";
		complete_location_from_location_using_location_as_buffer(location_2, location_1, location_3, location_2_end, "Location 2", "Location 1", "Location 3");
		print_current_state(location_1, location_2, location_3);

		// Since we need to solve location 1, we will move all items from location 1 to location 3 (on top of pre-existing items).
		cout << "\nSince we need to solve location 1, we will move all items from location 1 to location 3 (on top of pre-existing items).";
		move_location_to_location(location_1, location_3, "Location 1", "Location 3");
		print_current_state(location_1, location_2, location_3);

		// Now we can complete location 1 using the extra items left on location 3 using location 2 as a buffer. Keep in mind the function shouldn't remove extra items since it will revert the buffer and from locations every time a match is found.
		cout << "\nNow we can complete location 1 using the extra items left on location 3 using location 2 as a buffer. Keep in mind the function shouldn't remove extra items since it will revert the buffer after reaching the end of the stack.";
		complete_location_from_location_using_location_as_buffer(location_1, location_3, location_2, location_1_end, "Location 1", "Location 3", "Location 2");
		print_current_state(location_1, location_2, location_3);

		cout << "\n\n\n";
	}
}
