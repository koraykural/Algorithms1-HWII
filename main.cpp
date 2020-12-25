/**
 * Main function.
 * 
 * @author Koray Kural - 150170053
 * @date 25/12/2020
 */

#include <iostream> // cout
#include <fstream>  // ifstream
#include <stdlib.h> // srand()
#include <time.h>   // time()
#include <chrono>   // high_resolution_clock
#include "includes/MinHeap.h"
#include "includes/Location.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Validate cli arguments
    if (argc != 3)
    {
        cerr << "Argument count must be 3" << endl;
        return EXIT_FAILURE;
    }

    // Parse arguments to m and p
    int m = stoi(argv[1]);
    double p = stod(argv[2]);

    // Hard-coded location of hotel
    Location hotel = Location(33.40819, 39.19001);

    ifstream file;
    file.open("locations.txt");

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    // Read header line into dummy variable
    getline(file, line);

    MinHeap<double> distances;
    srand(time(NULL));
    int update_count = 0;
    int insert_count = 0;

    // Start time
    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i <= m; i++)
    {
        if (i % 100 == 0)
        {
            double called_taxi_distance = distances.get_min();
            cout << "Taxi called: " << called_taxi_distance << endl;
        }

        double random_number = (double)rand() / (RAND_MAX);

        // Update distance of a random taxi
        if (random_number < p && distances.get_size() > 0)
        {
            update_count++;
            int taxi_index = rand() % (distances.get_size());
            distances.update_value(taxi_index, distances[taxi_index] - 0.01);
        }

        // Add new taxi
        else
        {
            insert_count++;
            // Read country
            getline(file, line, ' ');
            double lng = stod(line);

            // Read item type
            getline(file, line, '\n');
            double lat = stod(line);

            Location taxi = Location(lng, lat);
            distances.insert(taxi.calculate_distance(hotel));
        }
    }

    cout << "Number of update operations: " << update_count << endl;
    cout << "Number of insert operations: " << insert_count << endl;

    // End time
    auto stop = chrono::high_resolution_clock::now();

    // Calculate duration in miliseconds
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start) / 1000;
    cout << "Total runtime: " << duration.count() << "ms" << endl;

    file.close();
    return EXIT_SUCCESS;
}
