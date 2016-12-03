//
// Created by tadeze on 12/1/16.
//

#include "tools.h"
//using namespace std;
//using namespace std;

//using namespace arma;
/*
double median(std::vector<double> &observation){

    double meddd = std::sort(observation.begin(),observation.end());
    return meddd;

}*/
std::vector<std::vector<double> > readcsv(const char* filename, char delim ,
                                bool header) {
    std::vector < std::vector<double> > values;
    std::vector<double> valueline;
    std::ifstream fin(filename);
    std::string item;
    if (header)  //if header available
        getline(fin, item);

    for (std::string line; getline(fin, line);) {
        std::istringstream in(line);
        while (getline(in, item, delim)) {
            valueline.push_back(atof(item.c_str()));
        }
        values.push_back(valueline);
        valueline.clear();
    }
    return values;
}

std::vector<double> means(std::vector<std::vector<double> > points)
{
    double x=0.0,y=0.0,z=0.0;
    std::vector<double> xyz;
    int i=0;
    for(i=0;i<points.size();i++)
    {

        x+=points[i][0];
        y+=points[i][1];
        z+=points[i][2];
    }
    xyz.push_back(x/i);
    xyz.push_back(y/i);
    xyz.push_back(z/i);
    return xyz;

}
template <typename T>
T absolute(T value )
{
    return (T) value>0?value: -1*value;
}

float max(float a, float b)
{
    return a>b?a:b;
}

float medianR(std::vector<double> &observations,rAvg ravg)
{
    float dist = 0.0;
    std::vector<double> medd;
    float mn;
    int len = observations.size();
    if (ravg==MEAN)
    {
        for(int i=0;i<observations.size();i++)
        {
            dist +=observations[i];
        }

         mn = dist/(float)observations.size();
    }
    else if(ravg==MAX){
        for(int i=0;i<observations.size();i++)
        {
            dist =max(dist,observations[i]);
        }
    mn=dist;
    }
    else{ // for median
        std::sort(observations.begin(),observations.end());

        dist = len%2!=0?observations[(len-1)/2]:0.5*(observations[(len)/2] +observations[(len-2)/2]);
        mn = dist;
    }
        return mn;
}

cloudpp radiusXYZ(std::vector<int> &cluster, std::vector<std::vector<double> > &points,
rAvg distType)
{
    cloudpp cpp;
    float x=0.0,y=0.0,z=0.0;
    cpp.radiusX=0;cpp.radiusY=0.0;cpp.radiusZ=0.0;
    int len = cluster.size();

    for(int i=0;i<len;i++)
    {
        x+=points[cluster[i]][0];
        y+=points[cluster[i]][1];
        z+=points[cluster[i]][2];
    }
    cpp.x = x/len; cpp.y = y/len;cpp.z = z/len;

    std::vector<double> distX(len),distY(len),distZ(len);
    for(int i=0;i<len;i++)
    {
        //x = points[cluster[i]][0]-cpp.x;
        //x = absolute(x);
        distX[i]=(absolute(points[cluster[i]][0]-cpp.x));
        distY[i]=(absolute(points[cluster[i]][1]-cpp.y));
        distZ[i]=(absolute(points[cluster[i]][2]-cpp.z));
    }

    cpp.radiusX = medianR(distX,distType);
    cpp.radiusY = medianR(distY,distType);
    cpp.radiusZ = medianR(distZ,distType);
    return cpp;
}
