#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Bubble Sort
void bubbleSort(int arr[], int n, long long& comp_count, long long& swap_count) {
    bool swapped = true;
    int temp;

    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comp_count++;
            if (arr[j] > arr[j + 1]) {
                swapped = true;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap_count++;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n, long long& comp_count, long long& swap_count) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comp_count++;  
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                swap_count++;  
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}


// Heap Sort
void heapify(int arr[], int n, int i, long long& comp_count, long long& swap_count) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        comp_count++;
        if (arr[l] > arr[largest]) largest = l;
    }
    if (r < n) {
        comp_count++;
        if (arr[r] > arr[largest]) largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        swap_count++;
        heapify(arr, n, largest, comp_count, swap_count);
    }
}

void heapSort(int arr[], int n, long long& comp_count, long long& swap_count) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp_count, swap_count);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swap_count++;
        heapify(arr, i, 0, comp_count, swap_count);
    }
}

// Merge Sort
long long mergeCompCount;
long long mergeAssignCount;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        mergeAssignCount++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        mergeAssignCount++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        mergeCompCount++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
            mergeAssignCount++;
        } else {
            arr[k++] = R[j++];
            mergeAssignCount++;
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
        mergeAssignCount++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        mergeAssignCount++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Exchange Sort
void exchangeSort(int arr[], int n, long long& comp_count, long long& swap_count) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            comp_count++;
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swap_count++;
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int n, long long& comp_count, long long& swap_count) {
    int smallest;
    for (int i = 0; i < n - 1; i++) {
        smallest = i;
        for (int j = i + 1; j < n; j++) {
            comp_count++;
            if (arr[j] < arr[smallest]) {
                smallest = j;
            }
        }
        if (smallest != i) {
            int temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;
            swap_count++;
        }
    }
}

// Quicksort
void partition(int arr[], int low, int high, int& pivotpoint,
               long long& partition_count, long long& total_count,
               long long& compare_count, long long& swap_count) {
    partition_count++;
    total_count++;

    int pivotitem = arr[low];
    int j = low;

    for (int i = low + 1; i <= high; i++) {
        compare_count++;
        if (arr[i] < pivotitem) {
            j++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            swap_count++;
        }
    }

    pivotpoint = j;
    int tmp = arr[low];
    arr[low] = arr[pivotpoint];
    arr[pivotpoint] = tmp;
    swap_count++;
}

void quicksort(int arr[], int low, int high,
               long long& quicksort_count, long long& partition_count,
               long long& total_count, long long& compare_count, long long& swap_count) {
    if (low >= high) return;

    int pivotIndex = low + rand() % (high - low + 1);
    int temp = arr[low];
    arr[low] = arr[pivotIndex];
    arr[pivotIndex] = temp;
    swap_count++;

    quicksort_count++;
    total_count++;

    int pivotpoint = -1;
    partition(arr, low, high, pivotpoint,
              partition_count, total_count,
              compare_count, swap_count);

    quicksort(arr, low, pivotpoint - 1,
              quicksort_count, partition_count,
              total_count, compare_count, swap_count);
    quicksort(arr, pivotpoint + 1, high,
              quicksort_count, partition_count,
              total_count, compare_count, swap_count);
}

// Array Generators
int* generateAlmostSorted(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = i;
    if (n > 5) {
        swap(arr[n / 2], arr[n / 2 - 1]);
        swap(arr[n / 3], arr[n / 3 - 1]);
    }
    return arr;
}

int* generateRandom(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}

int* generateReverseSorted(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = n - i;
    return arr;
}

int* generateDuplicates(int n) {
    int* arr = new int[n];
    int vals[5] = {0, n / 4, n / 2, 3 * n / 4, n};
    for (int i = 0; i < n; i++) arr[i] = vals[rand() % 5];
    return arr;
}


int main() {
    srand(time(0));

    auto runSortsOnArray = [](const string& name, int* arr, int size) {
        unsigned long long start, end;

        
        // --- Bubble Sort ---
        {
            long long compCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            bubbleSort(tempArray, size, compCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Bubble Sort - " << name << " (n=" << size << ")\n";
            cout << "  Compares: " << compCount << "\n";
            cout << "  Swaps: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }
        // --- Insertion Sort ---
        {
            long long compCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            insertionSort(tempArray, size, compCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Insertion Sort - " << name << " (n=" << size << ")\n";
            cout << "  Compares: " << compCount << "\n";
            cout << "  Swaps/Shifts: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }

        // --- Exchange Sort ---
        {
            long long compCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            exchangeSort(tempArray, size, compCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Exchange Sort - " << name << " (n=" << size << ")\n";
            cout << "  Compares: " << compCount << "\n";
            cout << "  Swaps: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }

        // --- Selection Sort ---
        {
            long long compCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            selectionSort(tempArray, size, compCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Selection Sort - " << name << " (n=" << size << ")\n";
            cout << "  Compares: " << compCount << "\n";
            cout << "  Swaps: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }

        // --- Quicksort ---
        {
            long long quicksortCount = 0, partitionCount = 0;
            long long totalCount = 0, compareCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            quicksort(tempArray, 0, size - 1,
                      quicksortCount, partitionCount,
                      totalCount, compareCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Quicksort - " << name << " (n=" << size << ")\n";
            cout << "  Quicksort Calls: " << quicksortCount << "\n";
            cout << "  Partition Calls: " << partitionCount << "\n";
            cout << "  Total Calls: " << totalCount << "\n";
            cout << "  Compares: " << compareCount << "\n";
            cout << "  Swaps: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }

        // --- Merge Sort ---
        {
            mergeCompCount = 0;
            mergeAssignCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            mergeSort(tempArray, 0, size - 1);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Merge Sort - " << name << " (n=" << size << ")\n";
            cout << "  Comparisons: " << mergeCompCount << "\n";
            cout << "  Assignments: " << mergeAssignCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }
        // --- Heap Sort ---
        {
            long long compCount = 0, swapCount = 0;
            int* tempArray = new int[size];
            copy(arr, arr + size, tempArray);

            start = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            heapSort(tempArray, size, compCount, swapCount);
            end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            cout << "Heap Sort - " << name << " (n=" << size << ")\n";
            cout << "  Comparisons: " << compCount << "\n";
            cout << "  Swaps: " << swapCount << "\n";
            cout << "  Time (us): " << (end - start) << "\n\n";

            delete[] tempArray;
        }
    };

    int testArray[1000] = {320, 886, 92, 993, 445, 976, 429, 87, 165, 705, 598, 643, 6, 833, 911, 223, 647, 103, 544, 871, 496, 845, 838, 12, 446,
810, 644, 626, 764, 975, 892, 763, 668, 733, 561, 679, 106, 718, 881, 384, 461, 715, 448, 981, 162, 404, 7, 94, 310, 752, 732, 99, 181, 428,
597, 27, 464, 636, 684, 355, 560, 425, 375, 788, 252, 344, 215, 254, 189, 328, 682, 290, 781, 789, 813, 198, 207, 146, 790, 392, 258, 600,
547, 942, 516, 367, 491, 225, 579, 860, 926, 804, 282, 139, 922, 296, 793, 904, 624, 77, 455, 596, 823, 971, 977, 839, 859, 157, 637, 120,
321, 199, 699, 648, 564, 843, 453, 379, 465, 466, 505, 185, 535, 498, 351, 243, 71, 869, 753, 854, 33, 119, 531, 893, 741, 26, 510, 950, 812,
332, 484, 179, 237, 339, 798, 620, 154, 1000, 366, 147, 31, 17, 228, 330, 878, 378, 301, 548, 707, 877, 450, 541, 177, 386, 18, 744, 40, 232,
914, 292, 858, 916, 432, 299, 619, 640, 395, 986, 249, 760, 302, 645, 14, 941, 616, 210, 725, 173, 246, 304, 805, 818, 408, 728, 795, 100,
222, 834, 394, 946, 503, 857, 743, 32, 691, 476, 317, 711, 472, 3, 997, 137, 35, 563, 418, 49, 836, 360, 661, 778, 78, 81, 689, 963, 359, 370,
842, 108, 424, 925, 528, 454, 167, 599, 902, 338, 55, 540, 792, 8, 217, 652, 397, 41, 722, 325, 422, 241, 126, 573, 480, 349, 208, 358, 888,
796, 861, 196, 312, 870, 151, 153, 551, 513, 697, 635, 523, 915, 962, 42, 342, 952, 884, 749, 903, 724, 514, 820, 305, 152, 614, 539, 24, 784,
628, 47, 966, 615, 550, 401, 124, 811, 826, 621, 856, 336, 201, 387, 500, 474, 487, 730, 853, 416, 409, 102, 307, 758, 709, 489, 212, 116,
313, 284, 221, 747, 66, 775, 693, 69, 101, 759, 678, 768, 369, 269, 944, 729, 493, 664, 672, 537, 646, 37, 172, 587, 415, 899, 825, 291, 607,
114, 638, 86, 654, 726, 821, 586, 495, 141, 757, 895, 374, 710, 405, 190, 901, 714, 924, 274, 365, 511, 434, 440, 281, 527, 417, 674, 534,
382, 159, 255, 592, 2, 303, 133, 608, 954, 912, 935, 898, 786, 809, 270, 140, 266, 671, 75, 512, 549, 93, 110, 936, 68, 554, 931, 765, 80,
998, 874, 309, 611, 482, 97, 293, 244, 402, 323, 419, 107, 273, 276, 361, 56, 663, 184, 657, 272, 98, 420, 327, 82, 211, 203, 882, 675, 987,
138, 406, 456, 939, 734, 940, 745, 245, 239, 814, 72, 770, 623, 411, 937, 125, 216, 508, 470, 634, 802, 343, 205, 806, 777, 30, 435, 322, 388,
988, 381, 700, 145, 934, 224, 883, 891, 552, 403, 128, 447, 873, 951, 521, 350, 568, 257, 25, 90, 822, 585, 999, 306, 932, 622, 63, 584, 832,
504, 36, 978, 132, 45, 1, 533, 542, 135, 287, 740, 979, 412, 353, 59, 52, 696, 676, 991, 955, 149, 572, 785, 161, 28, 961, 475, 315, 819, 46,
717, 160, 737, 308, 569, 144, 756, 111, 701, 352, 617, 688, 220, 267, 192, 380, 444, 426, 969, 148, 967, 463, 601, 150, 721, 289, 766, 719, 5,
260, 867, 526, 326, 499, 20, 319, 670, 451, 865, 485, 960, 662, 437, 73, 187, 945, 669, 984, 529, 681, 713, 329, 783, 115, 459, 174, 39, 261,
594, 171, 575, 831, 692, 863, 195, 54, 927, 848, 277, 889, 591, 197, 155, 48, 143, 930, 655, 990, 441, 816, 773, 318, 21, 268, 690, 771, 347,
852, 314, 423, 348, 602, 735, 827,
565, 750, 685, 194, 683, 89, 16, 438, 85, 357, 800, 815, 188, 694, 285, 218, 191, 335, 164, 964, 134, 761, 769, 76, 929, 264, 994, 364, 507,
840, 543, 829, 589, 570, 202, 452, 996, 762, 943, 427, 182, 74, 88, 658, 462, 603, 706, 799, 649, 193, 439, 974, 501, 656, 471, 906, 803, 324,
577, 844, 371, 9, 230, 398, 502, 4, 43, 253, 479, 478, 410, 885, 311, 250, 995, 665, 413, 686, 19, 233, 736, 123, 553, 175, 918, 767, 209,
879, 755, 38, 251, 896, 96, 695, 469, 407, 680, 131, 235, 604, 558, 742, 231, 168, 633, 113, 875, 286, 333, 522, 949, 95, 980, 837, 612, 373,
631, 650, 70, 855, 846, 206, 368, 557, 851, 830, 213, 136, 880, 751, 473, 163, 142, 659, 262, 653, 538, 546, 519, 390, 118, 53, 376, 968, 776,
708, 121, 497, 431, 772, 156, 396, 117, 920, 84, 651, 595, 247, 278, 112, 566, 234, 817, 923, 79, 530, 436, 265, 774, 300, 559, 468, 787, 295,
567, 748, 331, 130, 876, 229, 849, 953, 956, 582, 400, 562, 62, 158, 259, 905, 109, 629, 746, 973, 393, 850, 864, 104, 723, 226, 283, 477, 11,
702, 590, 739, 556, 263, 275, 824, 630, 334, 22, 983, 83, 385, 868, 992, 57, 345, 894, 340, 716, 667, 443, 828, 67, 492, 297, 238, 703, 506,
256, 467, 15, 481, 60, 890, 791, 29, 399, 58, 509, 170, 341, 938, 958, 279, 176, 129, 605, 337, 532, 921, 957, 571, 660, 200, 363, 515, 346,
588, 712, 494, 808, 627, 51, 520, 985, 91, 807, 780, 947, 928, 65, 389, 242, 965, 910, 887, 574, 545, 44, 524, 356, 61, 430, 536, 779, 580,
458, 593, 835, 948, 214, 900, 64, 618, 186, 391, 609, 271, 578, 227, 959, 909, 576, 460, 433, 727, 517, 298, 913, 632, 34, 613, 933, 248, 383,
639, 377, 797, 754, 166, 280, 105, 698, 178, 704, 866, 731, 183, 583, 801, 518, 204, 897, 50, 907, 919, 982, 240, 989, 488, 219, 169, 555,
970, 13, 862, 581, 362, 642, 917, 294, 354, 316, 421, 236, 414, 677, 666, 525, 908, 180, 288, 372, 457, 10, 442, 490, 841, 782, 122, 483, 449,
720, 738, 606, 687, 127, 872, 610, 486, 972, 641, 23, 625, 847, 794, 673 }; 

    cout << "\n============================================================\n";
    cout << "Array Size = " << "1000" << "\n";
    cout << "============================================================\n";
    runSortsOnArray("Final Test", testArray, 1000);

/*
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        cout << "\n============================================================\n";
        cout << "Array Size = " << n << "\n";
        cout << "============================================================\n";

        int* almostSorted = generateAlmostSorted(n);
        int* randomArr = generateRandom(n);
        int* reverseSorted = generateReverseSorted(n);
        int* duplicates = generateDuplicates(n);

        runSortsOnArray("Almost Sorted", almostSorted, n);
        runSortsOnArray("Random", randomArr, n);
        runSortsOnArray("Reverse Sorted", reverseSorted, n);
        runSortsOnArray("Duplicates", duplicates, n);

        delete[] almostSorted;
        delete[] randomArr;
        delete[] reverseSorted;
        delete[] duplicates;
    }
*/
    return 0;
}
