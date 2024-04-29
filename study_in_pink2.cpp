#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int FakeWall :: getReqEXP() const 
{
   return req_exp;
}
Map :: Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
:num_rows(num_rows), num_cols(num_cols)
{
      map = new MapElement**[num_rows];
        for (int i = 0; i < num_rows; ++i) {
            map[i] = new MapElement*[num_cols];
            for (int j = 0; j < num_cols; ++j) {
                map[i][j] = new Path;
            }

        // Place Wall objects
        for (int i = 0; i < num_walls; ++i) {
            map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall;
        }

        // Place FakeWall objects
        for (int i = 0; i < num_fake_walls; ++i) {
            int x= array_fake_walls[i].getRow();
            int y= array_fake_walls[i].getCol();

            map[x][y] = new FakeWall((x*275+y*139+89)%900 +1 );
        }
    
    }
}
      

Map::~Map()
{
     for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
}

Position:: Position(const string & str_pos)
{
    int pos = str_pos.find(',');
    if(pos!= string::npos)
    {
        r=stoi(str_pos.substr(1,pos-1));
        c=stoi(str_pos.substr(pos+1,str_pos.length()-pos-2));  
    }


}
string Position::str() const
{
     return "(" + to_string(r) + "," + to_string(c) + ")";
}
bool Position::isEqual(int in_r,int in_c) const
{
   return (r==in_r && c==in_c);
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
/////////////////////////////////////////////intint