#include"maze.h"
#include<iostream>
using namespace std;
SquareMaze::SquareMaze()
{
    graph_.clear();
    width_=0;
    height_=0;
}
void SquareMaze::makeMaze(int width, int height)
{
    //initialize the vector that represent the graphs with all ceils closed
    width_ = width;
    height_ = height;
    graph_.clear();
    graph_.resize(width_*height_);
        //set bool value to 0, meaning that wall exists and  cannot travel
    for(size_t i=0; i<graph_.size();i++)
    {
        graph_[i].first=0;
        graph_[i].second=0;
    }
    //create disjoint sets
    DisjointSets sets_;
    sets_.addelements(width_*height_);
    //break the walls
        //end the loop when we only have one disjoint set
    while(sets_.size(0)!=width_*height_)
    {
        //generate randomt num [0,width) and [0,height) in each every loop
        int x_= rand() % width_;
        int y_ = rand() % height_;
            //right or down
        int choose_ = rand() % 2;
        //break wall if not in the same set
        if(choose_==0)
        {
            if(x_==width_-1) continue;
            if(sets_.find(x_+y_*width_) !=sets_.find(x_+1+y_*width_))
            {
                setWall(x_,y_,0,false);
                sets_.setunion(x_+y_*width_,x_+1+y_*width_);
            }
        }
        if(choose_==1)
        {
            if(y_==height_-1) continue;
            if(sets_.find(x_+y_*width_) !=sets_.find(x_+(y_+1)*width_))
            {
                setWall(x_,y_,1,false);
                sets_.setunion(x_+y_*width_,x_+(y_+1)*width_);
            }
        }
    }
    
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    //invalid input
    if(x<0||y<0||x>=width_||y>=height_)
        return false;
    //check
    if(dir==0)
    {
        return graph_[x+width_*y].first;
    }
    if(dir==1)
    {
        return graph_[x+width_*y].second;
    }   
    if(dir==2)
    {
        //already in the left most ceil
        if(x==0)    {return false;}
        return graph_[(x-1)+width_*y].first;
    }  
    if(dir==3)
    {
        //already in the left most ceil
        if(y==0)    {return false;}
        return graph_[x+width_*(y-1)].second;
    } 
    else
        return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    //boundary check
        //bottom
    if(y==height_-1&& dir==1)
    {
        return;
    }
        //right
    if(x==width_-1&&dir==0)
    {
        return;
    }
    //normal situation
    if(dir==0)
    {
        graph_[x+width_*y].first = !exists;
    }
    if(dir==1)
    {
        graph_[x+width_*y].second = !exists;
    }    
}

vector<int> SquareMaze::solveMaze()
{
    //bfs with queue
    queue<Cell> q_;             //cout<<q_.empty();
    q_.push(Cell(0,0));

    //initialize bool vector
    visited_.clear();
    visited_.resize(width_*height_);
    prev_.clear();
    prev_.resize(width_*height_);

    for(int i=0;i<graph_.size();i++)
    {
        visited_[i]=false;
    }

        //start point
    // visited_[0] = true;

   //not empty
    while(!q_.empty())
    {
        Cell cur_ = q_.front(); //cout<<cur_.x_;cout<<","<<cur_.y_<<endl;//exit(0);
        q_.pop();
        visited_[cur_.x_+cur_.y_*width_] = true;
        for(int i=0; i<=3; i++)
        {
            if(!canTravel(cur_.x_,cur_.y_,i)) continue;
            if(i==0&&cur_.x_!=width_-1 && visited_[cur_.x_+1+width_*cur_.y_]==false)     
            {
                q_.push(Cell(cur_.x_+1,cur_.y_));
                // visited_[cur_.x_+1+width_*cur_.y_]==true;
                prev_[cur_.x_+1+width_*cur_.y_] = cur_.x_+width_*cur_.y_;
            }
            if(i==1&&cur_.y_!=height_-1 &&visited_[cur_.x_+width_*(1+cur_.y_)]==false)   
            {
                q_.push(Cell(cur_.x_,cur_.y_+1));
                // visited_[cur_.x_+width_*(1+cur_.y_)]==true;
                prev_[cur_.x_+width_*(1+cur_.y_)] = cur_.x_+width_*cur_.y_;
            }
            if(i==2&&cur_.x_!=0 &&visited_[cur_.x_-1+width_*cur_.y_]==false)     
            {
                q_.push(Cell(cur_.x_-1,cur_.y_));
                // visited_[cur_.x_-1+width_*cur_.y_]==true;
                prev_[cur_.x_-1+width_*cur_.y_] = cur_.x_+width_*cur_.y_;
            }
            if(i==3&&cur_.y_!=0 &&visited_[cur_.x_+width_*(cur_.y_-1)]==false)   
            {
                q_.push(Cell(cur_.x_,cur_.y_-1));
                // visited_[cur_.x_+width_*(cur_.y_-1)]==true;
                prev_[cur_.x_+width_*(cur_.y_-1)] = cur_.x_+width_*cur_.y_;
            }
        }
        // cout<<"first"<<endl;
    }

// print prev's element elegantly
// for(int i = 0; i < height_; i++){
//     for(int j = 0; j < width_; j++){
//     cout << prev_[i*width_+j] << " ";
//     }
//     cout << endl;
// }
// exit(0);

    //find the dest and the longest distance 
    int cur_dist=0;
    int cur_dest = width_*(height_-1);
    for(int i=0;i<width_;i++)
    {
        int cur_p_ = width_*(height_-1)+i;
        int dist=0;
            //keep back traversal until we reach (0,0)
        int store_cur_p_ = cur_p_;
        while(cur_p_!=0)
        {
            cur_p_ = prev_[cur_p_];
            dist++;
        }
        //check update
        if(cur_dist<dist)
        {
            cur_dest=store_cur_p_;
            cur_dist=dist;
        } 
    }
// exit(0);
    //produce the output vector
    vector<int> ret_;
    int cur_p_ =cur_dest;
    destination=cur_dest;

// cout <<destination << "     ddd"<<endl;
// cout << cur_p_ << "     ddd"<<endl;

    while(cur_p_!=0)
    {
        int prev_p_ = prev_[cur_p_];
        if(cur_p_==prev_p_+1)
        {
            ret_.push_back(0);
        }
        if(cur_p_==prev_p_-1)
        {
            ret_.push_back(2);
        }
        if(cur_p_==prev_p_+width_)
        {
            ret_.push_back(1);
        }
        if(cur_p_==prev_p_-width_)
        {
            ret_.push_back(3);
        }
        cur_p_ = prev_p_;
    }
// exit(0);
    //reverse
    reverse(ret_.begin(),ret_.end());

// for(int i = 0; i < ret_.size(); i++){

//     cout << ret_[i] << " ";
//     cout << endl;
// }
// cout << ret_.size() << "     ddd"<<endl;
    return ret_;


}

PNG* SquareMaze::drawMaze() const
{
    //create png and resize it
    PNG* maze_png = new PNG();
    maze_png->resize(width_*10+1,height_*10+1);

    //blacken the entire topmost row
    maze_png->getPixel(0,0)->l=0;
    for(int i=10;i<maze_png->width();i++)
    {
        maze_png->getPixel(i,0)->l=0;  
    }
    //blacken the entire leftmost column
    for(int j=0;j<maze_png->height();j++)
    {
        maze_png->getPixel(0,j)->l=0;  
    }
    //blacken pixels accoording to walls
    for(int i=0;i<width_;i++)
    {
        for(int j=0;j<height_;j++)
        {
            //right wall exists
            if(graph_[i+j*width_].first==0)
            {
                //blacken corresponding pixels
                for(int k=0; k<=10;k++)
                {
                    maze_png->getPixel(10*(i+1),j*10+k)->l=0;
                }
            }
            //if bottom wall exists
            if(graph_[i+j*width_].second==0)
            {
                //blacken corresponding pixels
                for(int k=0; k<=10;k++)
                {
                    maze_png->getPixel(10*i+k,(j+1)*10)->l=0;
                }
            }
        }
    }
    return maze_png;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    solution_ = solveMaze();
    PNG* output_ =  drawMaze();
// exit(0);
    unsigned png_w = output_->width();
    unsigned png_h = output_->height();
    int x_pixel =5;
    int y_pixel =5;
    for(int i=0; i<solution_.size();i++)
    {
        if(solution_[i]==0)
        {
            for(int k=0; k<=10;k++)
            {
                output_->getPixel(x_pixel+k,y_pixel)->h=0;
                output_->getPixel(x_pixel+k,y_pixel)->s=1;
                output_->getPixel(x_pixel+k,y_pixel)->l=0.5;
                output_->getPixel(x_pixel+k,y_pixel)->a=1;
            }
            x_pixel+=10;
        }
        if(solution_[i]==1)
        {
            for(int k=0; k<=10;k++)
            {
                output_->getPixel(x_pixel,y_pixel+k)->h=0;
                output_->getPixel(x_pixel,y_pixel+k)->s=1;
                output_->getPixel(x_pixel,y_pixel+k)->l=0.5;
                output_->getPixel(x_pixel,y_pixel+k)->a=1;
            }
            y_pixel+=10;
        }
        if(solution_[i]==2)
        {
            for(int k=0; k<=10;k++)
            {
                output_->getPixel(x_pixel-k,y_pixel)->h=0;
                output_->getPixel(x_pixel-k,y_pixel)->s=1;
                output_->getPixel(x_pixel-k,y_pixel)->l=0.5;
                output_->getPixel(x_pixel-k,y_pixel)->a=1;
            }
            x_pixel-=10;
        }
        if(solution_[i]==3)
        {
            for(int k=0; k<=10;k++)
            {
                output_->getPixel(x_pixel,y_pixel-k)->h=0;
                output_->getPixel(x_pixel,y_pixel-k)->s=1;
                output_->getPixel(x_pixel,y_pixel-k)->l=0.5;
                output_->getPixel(x_pixel,y_pixel-k)->a=1;
            }
            y_pixel-=10;
        }
    }

// cout<<destination<<endl;
// exit(0);
    //make the exit
    int dest_x = destination-width_*(height_-1);
    for(int k=1;k<=9;k++)
    {
        output_->getPixel(dest_x*10+k,(height_)*10)->l=1;
    }
    return output_;
}