#include "conv.h"
#include "jpeg.h"

#include <iostream>
#include <vector>
using namespace std;

vector<vector<vector<int>>> filterImage(marengo::jpeg::Image &img, vector<vector<vector<float>>> &filter, int divison_factor)
{
    // Get image and filter details
    size_t  img_x = img.getWidth(),
            img_y = img.getHeight(),
            img_d = img.getPixelSize();

    size_t  fil_x = filter[0].size(),
            fil_y = filter.size(),
            fil_d = filter[0][0].size();

    // Determine output size
    size_t  out_x = img_x - fil_x + 1,
            out_y = img_y - fil_y + 1;

    if((img_x < fil_x) || (img_y < fil_y) || (img_d != fil_d))
    {
        throw out_of_range( "Image height and width can't be lower than filter mask and dimensions must be same" );
    }
    
    // Initialize output vector array
    vector<vector<vector<int>>> output(out_y, vector<vector<int>> (out_x, vector<int> (fil_d, 0)));

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
                }
            }
        }
    }
    
    return output;
}
