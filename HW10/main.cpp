#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
        for (int j2 = 0; j2 < h; j2++) {
          const Color& c = input.GetPixel(i2,j2);      
          // skip all pixels that are not black
          if (!c.isBlack()) continue;
          // calculate the distance between the two pixels
          double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
          // store the closest distance to a black pixel
          if (closest < 0 || distance < closest) {
            closest = distance;
          }
        }
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}

//This fucntion imporves on the naive method by finding all the black pixels first,
//so we do not loop through all the pixels an extra time for each pixel accessed.
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  std::vector<std::pair<int, int> > blackpoints;
  //loop through all pixels and add balck pixels to a vector of pairs which contains the
  //coordinates of the black points
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      const Color& c = input.GetPixel(i,j);      
      // skip all pixels that are not black
      if (c.isBlack()){
        blackpoints.push_back({i,j});
      }
    }
  }
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over the black pixels in the vector and find the distance from each
      //one
      for (unsigned int k = 0; k < blackpoints.size(); k++)  {
        int i2 = blackpoints[k].first;
        int j2 = blackpoints[k].second;
        double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
        // store the closest distance to a black pixel
        if (closest < 0 || distance < closest) {
          closest = distance;
        }
      }
      
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;

}

//functiona takes in the middle pixel and its coordinates, the height and width of the
//image, the priority queue and imput and distance field images. This function edits the
//priority queue and propagates the distance data of the middle pixel p to its 8 neighbor
void checkNeighbors(const DistancePixel* p, int xval, int yval, int w, int h,
DistancePixel_PriorityQueue& queue, double& answer, Image<Color> &input,
Image<DistancePixel> &distance_image){
  //go through all 8 directions
  for(int i = -1; i<=1; i++){
    for(int j = -1; j<=1; j++){
      //skip if differential is 0(on current spot)
      if(i==0 && j==0) continue;
      //skip if out of bounds
      if(xval + i < 0 || xval + i >= h || yval + j < 0 || yval + j >= w) continue;
      //find color of neighbor
      Color& col = input.GetPixel(xval +i, yval +j);
      DistancePixel& neighbor = distance_image.GetPixel(xval +i,yval +j);
      if(col.isBlack()) continue;
      else{
        double distance = sqrt((i)*(i) + (j)*(j));
        //calculate whether adding the distance from the middle pixel to the value of
        //the middle pixel
        if(distance + p->getValue() < neighbor.getValue()){
          //change value of answer to be largest distance value in whole distance field
          if(distance + p->getValue() > answer)
            answer = distance + p->getValue();
          neighbor.setValue(distance + p->getValue());
          //if already red, update position
          if(col.r != 0){
            queue.update_position(&neighbor);
          }
          //if not red, make red and add to queue
          else{
            col.b = 0;
            col.r = 255;
            queue.push(&neighbor);
          }
        } 
      }
    }
  }
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  DistancePixel_PriorityQueue queue;
  int w = input.Width();
  int h = input.Height();
  double answer = 0;
  //create vector with all the coordinates of black points in the initial image
  std::vector<std::pair<int, int> > blackpoints;
  for (int i = h-1; i >=0 ; i--)  {
    for (int j = 0; j < w; j++) {
      Color& c = input.GetPixel(i,j);      
      // skip all pixels that are not black
      DistancePixel& p = distance_image.GetPixel(i,j);
      //black pixels have value 0
      if (c.isBlack()){
        blackpoints.push_back({i,j});
        p.setValue(0);
      }
      //everything else shoudl be blue with a very high initial value
      else{
        c.r = 0;
        c.g = 0;
        c.b = 255;
        p.setValue(100000);
      }
      p.setX(i);
      p.setY(j);
    }
  }
  //loop through all the black points and propagate distance data to all its neighbors,
  //making them red and adding them to the queue through the checkNeighbors function
  for(unsigned int k = 0; k<blackpoints.size(); k++){
    const DistancePixel* p = &(distance_image.GetPixel(blackpoints[k].first,
    blackpoints[k].second));
    checkNeighbors(p,p->getX(), p->getY(), w, h, queue, answer, input, distance_image);
  }
  //next, now that we have an initial prioroty queue, loop until it is empty and access
  //the top value , make it black, and porogate data to neighbors and add them to the
  //queue if neccessary. Then, remove the top value from the queue.
  while(queue.size() > 0){
    const DistancePixel* p = queue.top();
    Color& c = input.GetPixel(p->getX(),p->getY());
    c.b = 0;
    c.g = 0;
    c.r = 0;
    
    checkNeighbors(p,p->getX(), p->getY(), w, h, queue, answer, input, distance_image);
    queue.pop();
  }
  return answer;
}


// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
