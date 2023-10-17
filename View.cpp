#include <iostream>
#include "Filter.cpp"

void display()
{
    cout << "\n1- Black & White Filter\n\n";
    cout << "2- Invert Filter\n\n";
    cout << "3- Merge Filter \n\n";
    cout << "4- Flip Image\n\n";
    cout << "5- Rotate Image\n\n";
    cout << "6- Darken and Lighten Image\n\n";
    cout << "7- Detect Image Edges\n\n";
    cout << "8- Enlarge Image (Under progress)\n\n";
    cout << "9- Shrink Image (Under progress)\n\n";
    cout << "a- Mirror 1/2 Image\n\n";
    cout << "b- Shuffle Image (Under progress)\n\n";
    cout << "c- Blur Image (Under progress)\n\n";
    cout << "d- Crop Image (Under progress)\n\n";
    cout << "e- Skew Image Right (Under progress)\n\n";
    cout << "f- Skew Image Up (Under progress)\n\n";
    cout << "s- Save the image to a file\n\n";
    cout << "0- Exit\n\n";
}

void Main_view() {
    load_image();
    char op = '1';
    while (op != '0') {
        display();
        cout << "Enter Filter: ";
        cin >> op;
        switch (op) {
            case '1':
                Black_White();
                break;
            case '2':
                invert();
                break;
            case '3':
                mergeImage();
                break;
            case '4':
                Flib_image();
                break;  
            case '5':
                Rotate_image();
                break;
            case '6':
                darken_liten_image();
                break;
            case '7':
                detect_image_edges();
                break;
            case '8':
                Enlarge();
                break;
            case '9':
                shrinkImage();
                break;
            case 'a':
                mirror_image();
                break;
            case 'b':
                Shuffle_Image();
                break;
            case 'c':
                blurImage();
                break;
            case 'e':
                skew_horizontal();
                break;
            case 'd':
                crop_image();
                break;
            case 's':
                save_image();
                break;
        }
    }
}

