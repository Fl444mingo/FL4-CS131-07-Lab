#include <iostream>
using namespace std;
void sort(int pos, string *stringList, double *doubleList);
int main() {
    // Initialize ints used for setting and increasing size of array
    int pos = 0, capacity = 1;
    // Declare string input and string dynamic array/pointer
    string name, *nameList;
    // Declare number input and number dynamic array/pointer, and initialize sum to calculate behind the scenes
    double grade, sum = 0.0, *gradeList;
    // Assign memory locations for above pointers
    nameList = new string[capacity];
    gradeList = new double[capacity];
    // Setting float precision to always show two decimal places
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    // Flavor text intro
    cout << "Welcome to the Grade Averagerizer.\n\nPer line, enter a name and score, "
    "separated by a space.\nEnter \"Exit 0\" to end process and display statistics.\n\nData: ";
    // Receive initial input
    cin >> name >> grade;
    // While loop to keep receiving input until user satisfied
    do {
        // Because 1st value in array is ID 0, pos = capacity means capacity needs +1 to allow that pos to be valid
        if (pos >= capacity) {
            capacity++;
            // Initialize temporary, larger arrays to copy data into
            string* nameTemp = new string[capacity];
            double* gradeTemp = new double[capacity];
            // Copy data from original arrays into temporary arrays by incrementing from first to last value
            for (int i = 0; i < pos; i++) {
                nameTemp[i] = nameList[i];
                gradeTemp[i] = gradeList[i];
            }
            // Clear data from original arrays
            delete[] nameList, gradeList;
            // Copy data from expanded temporary arrays into now-fresh established arrays
            nameList = nameTemp;
            gradeList = gradeTemp;
        }
        // Append input to corresponding array
        nameList[pos] = name;
        gradeList[pos] = grade;
        // Advance pointer position
        pos++;
        // Update sum
        sum += grade;
        // New user input prompt
        cout << "Data: ";
        cin >> name >> grade;
    } while (name != "Exit");
    // Clear screen for a blank slate to restate user input and display statistics
    system("cls");
    // Average initialized here because sum and pos have reached their final values
    double average = sum / pos;
    // Stat display dependent on more than one data point existing
    if (pos > 0) {
        cout << "You entered:\n";
        // For loop to print out user input as entered
        for (int i = 0; i < pos; i++)
            cout << nameList[i] << " " << gradeList[i] << "\n";
        // Sort values to pick max and min from both ends of arrays
        sort(pos, nameList, gradeList);
        // Print last and then first value from both arrays, because they've been sorted lowest to highest
        cout << "\nThe highest score was " << nameList[capacity - 1] << " with a " << gradeList[capacity - 1]
        << "\nThe lowest score was " << nameList[0] << " with a " << gradeList[0] << "\n\n";
        // Declare a new array in which to store individual score deviation from calculated average
        double* deviations = new double[capacity];
        for (int i = 0; i < pos; i++) {
            // Absolute value of the difference between a given score and the average
            deviations[i] = fabs(average - gradeList[i]);
        }
        // Re-sort nameList from lowest to highest, this time corresponding to deviations
        sort(pos, nameList, deviations);
        // Print first value from both arrays, which is now the smallest deviation
        cout << "The average score was a " << average << ".\n" << "The score closest to the average was "
        << nameList[0] << ", who was only " << deviations[0]<< " points away.\n\n";
    }
    else
        cout << "Not enough grades to average\n";
    // "delete"s corresponding to "new"s to get in the habit of avoiding memory leaks
    delete[] nameList, gradeList;
    system("pause");
    return 0;
}
// Swap function to use in selection sorting function
void swap(int& a, int& b) {
    // Temporarily store first value (a)
    int temp = a;
    // Assign value b to a
    a = b;
    // Assign temp value (a) to b, now they are swapped
    b = temp;
}
// Bubble sorting function that sorts arrays in order from least to greatest
void sort(int pos, string *stringList, double *doubleList) {
    // Either pos or capacity could be used to compare to first, because they're both equal to array size
    // Loops through array, calling the swap function when necessary
    for (int first = 0; first < pos; first++) {
        // Assume first value in comparison is smaller
        int small = first;
        // Loops through array, changing small to the next value if it instead is smaller
        for (int next = first + 1; next < pos; next++)
            if (doubleList[next] < doubleList[small]) small = next;
        // If we have determined the next value is smaller, swap them to correct the order
        if (first != small)
            // Use same position swap sort function on both arrays at the same time, so the string value
            // stays at the same position as its corresponding double value within its respective array
            swap(stringList[first], stringList[small]), swap(doubleList[first], doubleList[small]);
    }
}