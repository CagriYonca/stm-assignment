#include "jpeg.h"
#include "conv.h"
#include <iostream>
#include <time.h>

using namespace std;

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        cout << "No jpeg file specified\n";
        return 1;
    }
    try
    {
        using namespace marengo::jpeg;
        
        // Initialize image and output output vector array
        Image img( argv[1] );
        vector<vector<vector<int>>> filtered_img;

        // Customize your filter mask
        vector<vector<vector<float>>> filter_mask {
            {{1,1,1}, {2,2,2}, {1,1,1}},
            {{2,2,2}, {4,4,4}, {2,2,2}},
            {{1,1,1}, {2,2,2}, {1,1,1}} };
        
        // Filter image with mask and divide to division factor
        filtered_img = filterImage(img, filter_mask, 16);

        // Transform vector array to image and save
        img.transform(filtered_img);
        img.save("filtered.jpg", 100);

        return 0;
    }
    catch( const exception& e )
    {
        cout << "Main() error handler: ";
        cout << e.what() << endl;
        return 1;
    }
}
