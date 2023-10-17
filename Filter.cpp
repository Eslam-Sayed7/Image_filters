#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <unistd.h>
#include <cmath>

unsigned char image[SIZE][SIZE];


// to test the code you should to creat a folder with the name "images" 
// and put the image you want to test as long as it .bmp and 256 * 256
// and to save the image, you should to create a folder with the name "Editing".

void load_image()
{
    string imageName;
    string path = "\\images\\";
    cout << "Enter the source image file name: ";
    cin >> imageName;
    path += imageName;
    char cwd[PATH_MAX];
    strcat(getcwd(cwd, sizeof(cwd)), path.c_str());
    strcat(cwd, ".bmp");
    readGSBMP(cwd, image);
}

void save_image()
{
    string imageName, path = "\\Editing\\";
    cout << "Enter the targer image file name: ";
    cin >> imageName;
    path += imageName;
    char cwd[PATH_MAX];
    strcat(getcwd(cwd, sizeof(cwd)), path.c_str());
    strcat(cwd, ".bmp");
    writeGSBMP(cwd, image);
}

// --------------youssefHosssam-----------------
// Filter 1: Black and White Image
void Black_White()
{
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (image[i][j] > 127){
                image[i][j] = 255;
            } else {
                image[i][j] = 0;
            }    
        }
    }
}

// Filter 4: Flip Image
void Flib_image()
{
    cout << "Flip (h)orizontally or (v)ertically ? ";
    char dir;
    cin >> dir;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE / 2; ++j) {
            if (dir == 'h'){
                swap(image[j][i], image[SIZE - j][i]);
            }
            else{
                swap(image[i][j], image[i][SIZE - j]);
            }
        }
    }
}

// Filter a: Mirror Image
void mirror_image()
{
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    char dir;
    cin >> dir;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE / 2; ++j) {
            if (dir == 'l')
                image[i][SIZE - j] = image[i][j];
            else if (dir == 'r')
                image[i][j] = image[i][SIZE - j];
            else if (dir == 'u')
                image[SIZE - j][i] = image[j][i];
            else if (dir == 'd')
                image[j][i] = image[SIZE - j][i];
        }
    }
}

// Filter 7: Detect Image Edges
void detect_image_edges()
{
    for (int i = 0; i < SIZE - 1; ++i){
        for (int j = 0; j < SIZE; ++j) {
            if (abs(image[i][j] - image[i + 1][j]) >= 28)
                image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }
}

// Filter d: Crop Image
void crop_image()
{
    cout << "Please enter x y l w: ";
    int x, y, l, w;
    y = 255 - y;
    cin >> x >> y >> l >> w;
    int last_x = x + w;
    int last_y = y + l;
    for (int i = 0 ; i < SIZE ; ++i){
        for (int j = 0 ; j < SIZE ; ++j) {
            if (i >= y && i <= last_y && j >= x && j <= last_x);
            else
                image[i][j] = 255;
        }
    }
}

// -------------------Eslam-Sayed7--------------------


// Filter 2: Invert Image
void invert()
{
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            image[i][j] = 255 - image[i][j];
        }
    }
}

// Filter 5: Rotate Image 

void Rotate_90()
{   // Rotating the image by 90 degrees
    // making temporary 2D array for the image to rotate every pexel and then swaping the whole two images
    unsigned char edited_image[SIZE][SIZE];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            edited_image[j][SIZE - i - 1] = image[i][j];
        }
    }
    // swaping new image with the inputed one
    swap(edited_image, image);
}

void Rotate_image()
{

    cout << "90 or 180 or 270 degrees ? notice : its clockwise rotation\n";
    int rotation_degree;
    cin >> rotation_degree;

    if (rotation_degree == 90){
        Rotate_90();
    }
    else if (rotation_degree == 180) {
        Rotate_90();
        Rotate_90();
    }
    else if (rotation_degree == 270) {
        Rotate_90();
        Rotate_90();
        Rotate_90();
    }
}

// Filter 8: Enlarge Image 

void Scaling(int row_s , int row , int column_s , int column ){
    unsigned char edited_image[SIZE][SIZE];
    // row_s is starting row to copy from
    // cnt_r is a counter to the copied pixels in the new 2D array and then repeat every pixel four times
    // column_s is starting column to copy from
    // cnt_c is a counter to the copied pixels in the new 2D array and then repeat every pixel four times
    //cnt_r --> rows
    //cnt_c --> columns
    
    for (int i = row_s , cnt_r = 0; i < row , cnt_r < 128 ; ++i , ++cnt_r) {
        for (int j = column_s , cnt_c = 0; j < column , cnt_c < 128; ++j , ++cnt_c)  {
            edited_image[2 * cnt_r][2 * cnt_c] = image[i][j];
            edited_image[2 * cnt_r][2 * cnt_c + 1] = image[i][j];
            edited_image[2 * cnt_r + 1][2 * cnt_c] = image[i][j];
            edited_image[2 * cnt_r + 1][2 * cnt_c + 1] = image[i][j];
        }
    }
    swap(edited_image , image);
}

void Enlarge(){

    cout << "Which quarter you want to enlarge ? 1 , 2 , 3 , 4\n";
    int quarter;
    cin >> quarter;
    if (quarter == 1)  {
        Scaling(0 , 128 , 0, 128);   
    } else if (quarter == 2)  {
        Scaling(0 , 128 , 129, 256);
    } else if (quarter == 3)  {
        Scaling(128 , 256 , 0, 128);
    } else if (quarter == 4) {
        Scaling(128 , 256 , 128, 256);
    } else {
        cout << "Please enter a valid number 1 - 4\n";
    }
    
}

// Filter b: Shuffle Image
void Shuffle_Image(){
    unsigned char edited_image[SIZE][SIZE];
    #define matrix pair<pair<int , int> , pair<int , int>>
    
    int parts = 4; 
    // {{ row_start, row_end }, { column_start , column_end }}
    matrix q_1_Matrix , q_2_Matrix  , q_3_Matrix , q_4_Matrix , input , output;

    q_1_Matrix = make_pair(make_pair(0, 128), make_pair(0, 128));
    q_2_Matrix = make_pair(make_pair(0, 128), make_pair(128, 256));
    q_3_Matrix = make_pair(make_pair(128, 256), make_pair(0, 128));
    q_4_Matrix = make_pair(make_pair(128, 256), make_pair(128, 256));

    auto copy_quarter = [&edited_image](matrix input , matrix output){
        //            input_row_start         output_row_start          input_row_end           output_row_end
        for (int i = input.first.first , l = output.first.first  ; i < input.first.second , l < output.first.second;  ++i , ++l) {
        //             input_column_start         output_column_start        input_column_end           output_column_end
            for (int j = input.second.first , m = output.second.first; j < input.second.second  , m < output.second.second; ++j , ++m){
                edited_image[l][m] = image[i][j];   
            }
        }
    };

    matrix arr_outputs[4] = {q_1_Matrix , q_2_Matrix , q_3_Matrix , q_4_Matrix};
    int pos = 0; // for iterating over the array of the matrices

    cout << "Enter the new order you want for the image\n";
    
    int Quarter ; // quarters user will input
    while (parts--) {
        cin >> Quarter;
        if (Quarter == 1) {
            input = q_1_Matrix;
            copy_quarter(input , arr_outputs[pos++]);
        } else if (Quarter == 2) {
            input = q_2_Matrix;
            copy_quarter(input , arr_outputs[pos++]);
        }else if (Quarter == 3) {
            input = q_3_Matrix;
            copy_quarter(input , arr_outputs[pos++]);
        }else if (Quarter == 4) {
            input = q_4_Matrix;
            copy_quarter(input , arr_outputs[pos++]);
        }

    }
    
    swap(edited_image , image);
    
}


void skew_horizontal(){  // under progress
   
}



// ------------Abdullah------------------------

// Filter 9: Shrink Image
void shrinkImage() {
unsigned char newImage[SIZE][SIZE];
    int op;

    cout << "would you like to shrink the image (1/2) press 1: \n"
            "or (1/3) press 2: \n"
            "or(1/4) press 3: \n";

    cin >> op;

    switch (op) {

        case 1:
            for (int i = 0, o = 0; i < SIZE; i += 2, o++) {
                for (int j = 0, x = 0; j < SIZE; j += 2, x++) {

                    //--------Take the average pixels we are going to compress.--------------------


                    newImage[o][x] = (image[i][j] + image[i + 1][j] + image[i][j + 1] +
                                      image[i + 1][j + 1]) / 4;

                }
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    if (i < 128 && j < 128) {
                        image[i][j] = newImage[i][j];

                    } else {
                        image[i][j] = 255;

                    }
                }
            }
            break;
        case 2:
            for (int i = 0, o = 0; i < SIZE; i += 3, o++) {
                for (int j = 0, x = 0; j < SIZE; j += 3, x++) {

                    //------------Take the average pixels we are going to compress.-----------------------

                    newImage[o][x] =
                            (image[i][j] + image[i][j + 1] + image[i][j + 2] + image[i + 1][j] + image[i + 1][j + 1]
                             + image[i + 1][j + 2] + image[i + 2][j] + image[i + 2][j + 1] + image[i + 2][j + 2]) / 9;


                }
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    if (i < 86 && j < 86) {
                        image[i][j] = newImage[i][j];

                    } else {
                        image[i][j] = 255;

                    }
                }
            }

            break;


        case 3:
            for (int i = 0, o = 0; i < SIZE; i += 4, o++) {
                for (int j = 0, x = 0; j < SIZE; j += 4, x++) {

                    //------------Take the average pixels we are going to compress.-----------------------

                    newImage[o][x] =
                            (image[i][j] + image[i][j + 1] + image[i][j + 2] + image[i][j + 3] + image[i + 1][j] +
                             image[i + 1][j + 1]
                             + image[i + 1][j + 2] + image[i + 1][j + 3] + image[i + 2][j] + image[i + 2][j + 1] +
                             image[i + 2][j + 2] + image[i + 2][j + 3]
                             + image[i + 3][j] + image[i + 3][j + 1] + image[i + 3][j + 2] + image[i + 3][j + 3]) / 16;


                }
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    if (i < 64 && j < 64) {
                        image[i][j] = newImage[i][j];

                    } else {
                        image[i][j] = 255;

                    }
                }
            }

            break;
    }
}

//Filter 3: Merge Images
void mergeImage()
{
    unsigned char image2[SIZE][SIZE];

    //-----------------load second image------------------------
    cout << "Enter the source second image file name: ";
    string imageName;
    string path = "\\images\\";
    cin >> imageName;
    path += imageName;
    char cwd[PATH_MAX];
    strcat(getcwd(cwd, sizeof(cwd)), path.c_str());
    strcat(cwd, ".bmp");
    readGSBMP(cwd, image2);

    //------------------------------------------------------------

    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
            
}

// Filter 6: Darken and Lighten Image
void darken_liten_image() {
    cout << "Would you like to make it darker press d or lighter press l: ";
    char op;
    cin >> op;

    for (int i = 0 ; i < SIZE ; ++i){
        for (int j = 0 ; j < SIZE ; ++j) {
            if (op == 'd'){
                image[i][j] /= 2;
            } else if (op == 'l') {
                int tmp = (255 - image[i][j]) / 2;   
                image[i][j] += tmp;
            }
        }
    }
}

// Filter c: Blur Image
void blurImage(){
    int x = 5;
    while (x--) {
        for (int i = 0; i <= SIZE; i++) {
            for (int j = 0; j <= SIZE; j++) {
                //-------the middile pixels----------------------
                if (i != 0 && i != 256 && j != 0 && j != 256) {

                    image[i][j] = (image[i][j] + image[i + 1][j] +
                                   image[i - 1][j] + image[i][j + 1] + image[i][j - 1]) / 5;
                }

                //-------the sides pixels----------------------
                if (i == 0 && j != 0 && j != 256) {
                    image[i][j] = (image[i][j] + image[i + 1][j] + image[i][j - 1] + image[i][j + 1]) / 4;


                } else if (i == 256 && j != 0 && j != 256) {
                    image[i][j] = (image[i][j] + image[i][j - 1] + image[i][j + 1] + image[i - 1][j]) / 4;


                } else if (j == 0 && i != 0 && i != 256) {
                    image[i][j] = (image[i][j] + image[i + 1][j] + image[i - 1][j] + image[i][j + 1]) / 4;


                } else if (j == 256 && i != 0 && i != 256) {
                    image[i][j] = (image[i][j] + image[i - 1][j] + image[i][j - 1] + image[i + 1][j]) / 4;

                }
            }
        }
    }
}

// Filter f: Skew Vertically 
void skew_verticall()
{

}