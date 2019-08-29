#include "jpeg.h"
#include <iostream>

using namespace std;

vector<vector<vector<int>>> filterImage(marengo::jpeg::Image &img, vector<vector<vector<float>>> &filter, int divison_factor)
{
    size_t img_x = img.getWidth(),
            img_y = img.getHeight(),
            img_d = img.getPixelSize();

    size_t fil_x = filter[0].size(),
            fil_y = filter.size(),
            fil_d = filter[0][0].size();

    size_t out_x = img_x - fil_x + 1,
        out_y = img_y - fil_y + 1;
    
    cout << img_x << " " << img_y << endl;

    vector<vector<vector<int>>> output(out_y, vector<vector<int>> (out_x, vector<int> (fil_d, 0)));

    if((img_x < fil_x) || (img_y < fil_y) || (img_d != fil_d))
    {
        throw out_of_range( "Image height and width can't be lower than filter mask and dimensions must be same" );
    }

    size_t i, j, fi, fj, k;
    vector<uint8_t> i_vec;

    for(j = 0; j < out_y; j++)
    {
        for(i = 0; i < out_x; i++)
        {
            for(k = 0; k < fil_d; k++)
            {
                for(fj = j; fj < j + fil_y; fj++)   
                {
                    for(fi = i; fi < i + fil_x; fi++)
                    {
                        i_vec = img.getPixel(fi, fj);
                        output[j][i][k] += (filter[fj - j][fi - i][k] / divison_factor) * i_vec[k];
                        i_vec.clear();
                    }
                }/*
                if(output[j][i][k] < 0)
                {
                    output[j][i][k] = 0;
                }*/
            }
        }
    }
    
    return output;
}

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
        Image imgOriginal( argv[1] );
        
        Image img = imgOriginal;
        vector<vector<vector<int>>> filtered_img;

        // Define 3x3x3 filter mask
        vector<vector<vector<float>>> filter_mask {
            {{1,1,1}, {2,2,2}, {1,1,1}},
            {{2,2,2}, {4,4,4}, {2,2,2}},
            {{1,1,1}, {2,2,2}, {1,1,1}} };
        
        cout << filter_mask[0][0][0] << endl;

        filtered_img = filterImage(img, filter_mask, 16);
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
