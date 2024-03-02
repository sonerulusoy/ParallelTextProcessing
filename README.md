# Parallel Text Processing with OpenMP

This project demonstrates parallel text processing using OpenMP. It reads sentences from a file, calculates the total number of characters and words in the sentences, and measures the performance using different numbers of threads.

## Prerequisites

Before running the program, make sure you have the following installed:

- C compiler (e.g., GCC)
- OpenMP library

## Usage

1. Clone the repository: git clone https://github.com/sonerulusoy/ParallelTextProcessing.git
2. Compile the program: gcc -fopenmp main.c -o text_processing
3. Run the program: ./text_processing


## File Format

The program expects a file named `sentences.txt` in the same directory containing the sentences to be processed. Each sentence should be on a separate line.

## Results

The program will output the total number of characters and words in the sentences, along with the elapsed time for each number of threads tested.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


