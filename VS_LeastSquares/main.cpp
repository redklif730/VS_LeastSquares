#include "string"
#include "Matrix.h"
#include "fstream"

using namespace std;


struct list_coords {
    precision_type x, y;
    list_coords* next_ptr;
};
struct list_elm {
    int num;
    precision_type value;
    list_elm* next_ptr;
};

list_coords* dots_list = nullptr;//coords from input file
list_elm* array_sum_list = nullptr;//sum_matrix

void show_list_coords();
void clear_list_coords();
void clear_list_elm();
void Getting_Started(int &power);
void sum_matrix(precision_type**& arr, int  power);
precision_type array_sum(list_elm*& start_line, list_elm*& prev_elm, const int& i, const int& j, const int& power);
precision_type sum_x_coords_in_power(const int& power);
void sum_y_coords_in_power(precision_type*& arr, const int& power);

int main() {
    //matrix_test();
    list_coords* cur_elm = dots_list, * prev_elm = nullptr;
    precision_type** least_squres_matrix, * least_squres_matrix_add_col;
    int power = 2;

    Getting_Started(power);
    //show_list_coords();
    sum_matrix(least_squres_matrix, power);//CHANGE TO MATRIX
    sum_y_coords_in_power(least_squres_matrix_add_col, power);

    Matrix A(power + 1);
    for (int i = 0; i < power + 1; i++)
        for (int j = 0; j < power + 1; j++)
            A[i][j] = least_squres_matrix[i][j];
    //cout << "matrix least_squres_matrix:" << endl;
    //A.show();
    Matrix Y(power + 1, 1);
    for (int i = 0; i < power + 1; i++)
        Y[i][0] = least_squres_matrix_add_col[i];
    //Y.show();
    //cout << "\n\n\n" << endl;
    Matrix B = (A.transpose() * A).inverse() * (A.transpose());
    //B.show();
    B *= Y;
    B.show();

    //end of execution
    //clear all dynamic elements not included in Class (cleared via destructors)
    clear_list_coords();
    clear_list_elm();
}

void Getting_Started(int& power) {
    ifstream File;
    string File_name, str;
    int n = 0, pos = 0;
    //digit indicates cur digit of value after point
    precision_type num, digit = 1;
    list_coords* prev_elm = nullptr, * cur_elm = nullptr;
    bool x_f = false, y_f = false, sign = false, write = false;
    while (!File.is_open()) {
        if (File_name.empty()) {
            cout << "Enter name of file with data to work with" << endl;
            getline(cin, File_name, '\n');
            if (File_name.find('.') == string::npos) {
                cout << "adding expansion\n";
                File_name += ".txt";
            }
            File.open(File_name, ios::in);
            if (!File.is_open()) {
                cout << "File doesn't exist" << endl;
                File_name = "";
            }
        }
    }
    cout << "File was opened" << endl;
    pos = 0;
    while (!File.eof()) {
        pos = 0;
        digit = 1;
        num = 0;
        cur_elm = new list_coords;
        //it's expected? that we have only 2 coords - x and y respectfully'
        x_f = false;
        y_f = false;
        write = false;
        cur_elm->x = 0;
        cur_elm->y = 0;
        getline(File, str, '\n');
        str += ' ';
        //cout << str << endl;
        while (pos < str.size()) {
            //cout << "str["<<pos<<"]=\'"<<str[pos]<<'\''<<endl;
            //cout << num << endl;
            if (str[pos] > '0' - 1 && str[pos] < '9' + 1) {
                if (digit == 1)//numbers before .
                    num = num * 10 + (str[pos] - '0') * (1 - 2 * sign);
                else {//after .
                    num += (str[pos] - '0') * digit * (1 - 2 * sign);
                    //cout << "arr[i]: "<<arr[i]<<" num_digit="<<(str[pos]-'0')*digit<<" digit="<<digit<<endl;
                    digit /= 10;
                }
                pos++;
                write = true;
            }
            else if (str[pos] == '-' && num == 0) {
                pos++;
                sign = true;
            }
            else if (str[pos] == '.' || str[pos] == ',') {//double part isn't needed
                pos++;
                digit = 0.1;
                //cout << "digit="<<digit<<' '<<double(1)/10<<endl;
            }
            else {
                if (!x_f && write) {
                    cur_elm->x = num;
                    x_f = true;
                    write = false;
                    //cout << "x="<<cur_elm -> x<<  " ";
                    sign = false;
                }
                else if (write) {
                    cur_elm->y = num;
                    y_f = true;
                    //cout << "y="<<cur_elm -> y<<endl;
                    break;
                }
                //cout << "   str="<<str<<"   num=" << num << endl;
                num = 0;
                digit = 1;
                //pos=str.find(' ', pos);
                //if there're more elements in between'
                while ((str[pos] < '0' - 1 || str[pos]>'9' + 1) && str[pos] != '-' && pos < str.size())
                    pos++;
            }
        }
        if (x_f && y_f) {
            if (prev_elm == nullptr)
                dots_list = cur_elm;
            else
                prev_elm->next_ptr = cur_elm;
            n++;
            prev_elm = cur_elm;
            cur_elm->next_ptr = nullptr;
        }
        else
            delete cur_elm;
    }
    //cout << endl;
    File.close();
    cout << "Enter power of polynom to approximate dots(max=" << n - 1 << ")" << endl;
    power = -1; 
    while (power == -1 || power > n - 1 || power < 1) {
        cin >> power;
        cin.clear();
        cin.ignore(100, '\n');
    }
}

//copy_matrix(precision_type **&arg_arr, precision_type **&arg_arr, power)
//function which creates matrix for Least Squads
void sum_matrix(precision_type**& arr, int  power) {
    list_elm* start_line = array_sum_list, * prev_elm = nullptr;
    arr = new precision_type * [power + 1];
    for (int i = 0; i < power + 1; i++) {
        arr[i] = new precision_type[power + 1];
        for (int j = 0; j < power + 1; j++)
            arr[i][j] = sum_x_coords_in_power(i + j);
    }
}

precision_type sum_x_coords_in_power(const int& power) {
    precision_type sum = 0, value = 1;
    list_coords* cur_elm = dots_list;
    while (cur_elm != nullptr) {
        value = 1;
        //cout << "cur_elm=" << cur_elm << " value=" << cur_elm->x << endl;
        for (int j = 0; j < power; j++)
            value *= cur_elm->x;//coords x
        //cout << "cur_sum="<<sum<<endl;
        sum += value;
        cur_elm = cur_elm->next_ptr;
    }
    //cout<<"sum_x="<<sum<<" in power="<<power<<endl;
    return sum;
}

void sum_y_coords_in_power(precision_type*& arr, const int& power) {//arr isn't nullptr
    precision_type sum = 0, value = 1;
    list_coords* cur_elm = dots_list;
    arr = new precision_type[power + 1];
    for (int k = 0; k < power + 1; k++) {
        sum = 0;
        cur_elm = dots_list;
        while (cur_elm != nullptr) {
            value = cur_elm->y;
            for (int j = 0; j < k; j++)
                value *= cur_elm->x;//coords x
            //cout <<"power="<<power<< " y_coords = "<<sum << endl;
            sum += value;
            cur_elm = cur_elm->next_ptr;
        }
        arr[k] = sum;
        //cout <<"	k="<<k<< " sum = "<<sum << endl;
    }
}


void show_list_coords() {
    list_coords* cur = dots_list;
    while (cur != nullptr) {
        cout << "(" << cur->x << ";" << cur->y << ")" << endl;
        cur = cur->next_ptr;
    }
}

void clear_list_coords() {
    if (dots_list != nullptr) {
        list_coords* cur = dots_list->next_ptr;
        //cout << "Deleting" << endl;
        while (cur != nullptr) {
            //cout << "(" << dots_list->x << ";" << dots_list->y << ")" << endl;
            delete dots_list;
            dots_list = cur;
            cur = cur->next_ptr;
        }
        delete dots_list;
    }
}
void clear_list_elm() {
    if (array_sum_list != nullptr) {
        list_elm* cur = array_sum_list->next_ptr;
        while (cur != nullptr) {
            delete array_sum_list;
            array_sum_list = cur;
            cur = cur->next_ptr;
        }
        delete array_sum_list;
    }
}

