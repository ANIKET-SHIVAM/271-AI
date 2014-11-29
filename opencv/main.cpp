#include "opencv.hpp"
#include "AI.hpp"
#include "trie.hpp"



Mat createOne(std::vector<cv::Mat> & images, int min_gap_size) {
    /*
    size_t cols = images.size()* ( images[0].cols + min_gap_size-1);
    images[0].rows;
    cv::Mat result = cv::Mat::zeros(images[0].rows+min_gap_size,cols,images[0].type());
    for (int i = 0; i < images.size(); i++) {
        cv::Mat to(result,Rect(images[0].cols*i+(min_gap_size-1)*i,0,images[0].cols,images[0].rows) );
        images[i].copyTo(to);
    }
    return result;
    */
    return Mat::zeros(1,1,1);
}
void thisMouseCallBack(int event, int x, int y, int flags, void *param) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        string s;
        cin >> s;
        imwrite("C:\\adt\\"+s+".png",mx);
    }
}
void maxLocs(const Mat& src, queue<Point>& dst, size_t size) {
    float maxValue = -1.0f * numeric_limits<float>::max();
    float* srcData = reinterpret_cast<float*>(src.data);
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            if(srcData[i*src.cols + j] >0.95) {
                maxValue = srcData[i*src.cols + j];
                dst.push(Point(j, i));
                if(dst.size() > size) {
                    dst.pop();
                }
            }
        }
    }
}
void MatchingMethod( int, void* ) {
    /// Source image to display
    Mat img_display;
    img.copyTo(img_display);
    /// Create the result matrix
    int result_cols =  img_display.cols - templ.cols + 1;
    int result_rows = img_display.rows - templ.rows + 1;
    result.create( result_cols, result_rows, CV_32FC1 );
    /// Do the Matching and Normalize
    matchTemplate( img_display, templ, result, match_method );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    /// Localizing the best match with minMaxLoc
    double minVal;
    double maxVal=2;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED ) {
        result = 1.0 - result;
    }
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED ) {
        matchLoc = minLoc;
    } else {
        matchLoc = maxLoc;
    }
    float x = ((float)(matchLoc.x))/ ((float)(img.cols /26));
    x  += ((float)(matchLoc.x+templ.cols)) / ((float)(img.cols/26));  //convert match coords to the appropriate letter 'A'-'Z'
    x/=2;
    L = 'A' + (int)(x);
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    /*
    imshow("templ",templ);
     imshow( image_window, img_display );
     imshow("result",result);
    waitKey(0);
    */
    return;
}

Mat& ftrImage(Mat &img, _RGB lowColor, _RGB rep,int radius, bool allbut = false) {
    for (int i =0; i <img.cols; i++)
        for(int j = 0; j < img.rows; j++) {
            Vec3b *intensity = &img.at<Vec3b>(j, i);
            uchar&blue = intensity->val[0];
            uchar &green = intensity->val[1];
            uchar&red = intensity->val[2];
            if (abs(red-lowColor.R) < radius && abs(green-lowColor.G) < radius&& abs(blue-lowColor.B) < radius) {
                if(!allbut) {
                    red=rep.R;
                    green=rep.G;
                    blue=rep.B;
                }
                //img.at<Vec3b>(j, i)=Vec3b(rep.B,rep.G,rep.R);
            } else if(allbut)
                red=blue=green=255;
        }
    return img;
}
int pixelCount(Mat &img, _RGB color) {
    int count=0;
    for (int i =0; i <img.cols; i++)
        for(int j = 0; j < img.rows; j++) {
            Vec3b *intensity = &img.at<Vec3b>(j, i);
            uchar&blue = intensity->val[0];
            uchar &green = intensity->val[1];
            uchar&red = intensity->val[2];
            if( red==color.R && blue==color.B && green ==color.G)
                count++;
        }
    return count;
}
void cleanImage(Mat& img) {
    //  Recently played LETTERS are white, we need uniform colors for all LETTERS.
    ftrImage(img,_RGB(255,255,255),_RGB(0,0,0),5); //replace shades of white with black letter color
    ftrImage(img,_RGB(76,25,0),_RGB(0,0,0),35);
    //Apply binary mask, all pixels not in the range of _RGB(0,0,0) + 0..10 are converted to white
    ftrImage(img,_RGB(0,0,0),_RGB(255,255,255), 10, true);
}
void updateState(char (&BOARD)[15][15], char (&LETTERS)[7]) {
    //run batch file to take screenshot via ADB
    system((ADB_DIR+"screen.bat").c_str());
    //check if file exists
    if (FILE *file = fopen((ADB_DIR+"screenshot.png").c_str(), "r"))
        fclose(file);
    else
        std::cout << "screenshot.png could not be found, check adb";
    Mat ogScreen = imread(String(ADB_DIR+"screenshot.png"));
    float factor = 2; //scaling factor
    //These offsets will need to be adjusted depending on the screenshot resolution your phone takes.
    //One way to find these offsets is to open screenshot in mspaint and put your mouseover
    int y_board = 500; //y offset of the top left corner of the game board in the screenshot
    int y_letters = 1570; //y offset of the top left corner of the LETTERS panel
    //crop gameboard and LETTERS panel from original screenshot
    //Scale to reasonable size
    Mat croppedBoard = ogScreen(Rect(0,y_board,ogScreen.cols,ogScreen.cols));
    Mat croppedLetters = ogScreen(Rect(0,y_letters,ogScreen.cols,160));
    resize(croppedBoard, croppedBoard, Size((int)(croppedBoard.cols/factor), (int) (croppedBoard.rows/factor)));
    resize(croppedLetters, croppedLetters, Size((int)(croppedLetters.cols/4), (int) (croppedLetters.rows/4)));
    //fix up image and enhance features for better template matching
    cleanImage(croppedBoard);
    cleanImage(croppedLetters);
    namedWindow( image_window, WINDOW_AUTOSIZE );
    namedWindow( result_window, WINDOW_AUTOSIZE );
    int bk = croppedBoard.cols/15; //this is the width of each block in every row/column.
    int lk = croppedLetters.cols/7; //width of every letter tile in the LETTERS panel
    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
    Mat all = imread("images/all.png");
    Mat abc = all;
    resize(abc,abc,Size(lk*26,croppedLetters.rows));
    cleanImage(abc);
    //imshow("all",abc);
    img = abc;
    for (int i = 0; i < 7; i++) {
        templ = croppedLetters(Rect(5+i*lk,5,lk-5,croppedLetters.rows-5));
        if ((float)pixelCount(templ,_RGB(255,255,255))/(templ.cols*templ.rows) > .95) {
            LETTERS[i]='_';
            continue;
        }
        //   imshow("t",templ);
        // waitKey(0);
        MatchingMethod(0,0);
        LETTERS[i]=L;
    }
    cout << endl;
    resize(all,all,Size(bk*26+3,bk+2));
    //waitKey(0);
    cleanImage(all);
    img=all;
    for (int i = 0; i <15; i++)
        for (int j=0; j<15; j++) {
            templ = croppedBoard(Rect(i*bk,j*bk,bk,bk));
            float whiteDensity =((float)(pixelCount(templ,_RGB(255,255,255))))/(bk*bk);
            if (whiteDensity > 0.94 )
                continue;
            MatchingMethod(0,0);
            BOARD[i][j] = L;
            // Alt_MatchingMethod(0,0);
        }
}

int main() {
    AI_Manager * AI = new AI_Manager();
    while ( AI->gameON) {
        updateState(AI->BOARD,  AI->LETTERS); //update game board and letters.
        AI->printBoard();
        AI->printLetters();
        //TODO:
        //Implement DFS and Trie Search
        //Add benchmark code here for report
        AI->getAllWords();
        AI->gameON = false;
    }
}