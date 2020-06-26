#include "neighbor.h"

Neighbor::Neighbor(int k) : k(k)
{

}

std::vector<Point> Neighbor::GetPoints() const
{
    return points;
}

bool Neighbor::GetData(std::string csv_file_path)
{
    std::string line;
    std::ifstream myfile(csv_file_path);

    if (!myfile.is_open())
        return false;

    while (!myfile.eof())
    {
        getline(myfile, line);
        if (line.size() == 0)
            break;

        std::vector <std::string> tokens = Tokenize(line, ',');
        QColor color;
        if(tokens[0]=="r")
            color = QColor(255,0,0);
        else
            color = QColor(0,0,255);

        int x = std::stoi(tokens[1]);
        int y = std::stoi(tokens[2]);
        points.push_back(Point(y,x,color));
    }
    return true;
}



void Neighbor::AddPoint(QPoint point)
{
    for(size_t i=0; i<points.size()-1; i++)
        for(size_t j=i+1; j<points.size(); j++)
        {
            if(EuclidianDistance(points[i].GetPoint(),point) > EuclidianDistance(points[j].GetPoint(), point))
            {
                auto p = points[i];
                auto q = points[j];
                points[i] = q;
                points[j] = p;
            }
        }
    int nrR = 0;
    int nrG = 0;
    for(int i=0; i<k; i++)
    {
        if(points[i].GetColor() == QColor(255,0,0))
            nrR++;
        else
            nrG++;

        // qDebug()<<EuclidianDistance(p.GetPoint(),point)<<"\n";
    }
    QColor c;
    if(nrR>nrG)
        c = QColor(255,0,0);
    else
        c = QColor(0,0,255);
     points.push_back(Point(point, c));
}

void Neighbor::AddPointWeight(QPoint point)
{
    for(size_t i=0; i<points.size()-1; i++)
        for(size_t j=i+1; j<points.size(); j++)
        {
            if(EuclidianDistance(points[i].GetPoint(),point) > EuclidianDistance(points[j].GetPoint(), point))
            {
                auto p = points[i];
                auto q = points[j];
                points[i] = q;
                points[j] = p;
            }
        }
    double nrR=0;
    double nrG=0;
    for(int i=0; i< k; i++)
    {
        if( points[i].GetColor() == QColor(255,0,0))
            nrR += EuclidianDistanceWeight(points[i].GetPoint(), point);
        else
            nrG += EuclidianDistanceWeight(points[i].GetPoint(), point);;
    }
    QColor c;
    if(nrR > nrG)
        c = QColor(255, 0, 0);
    else
        c = QColor(0, 0, 255);
     points.push_back(Point(point, c));
}

int Neighbor::CalculateMaxK()
{
    int minError=INT_MAX;
    int kVal = -1;
    for(int k=1; k< points.size();k++)
    {
        int nr=0;
        for(int i=0; i<points.size(); i++)
        {
            QColor color = GetColor(i);
            if(color != points[i].GetColor())
                nr++;
        }
        if(nr < minError)
        {
            minError = nr;
            kVal = k;
        }
    }
    return kVal;
}

std::vector<std::string> Neighbor::Tokenize(const std::string &str, const char delim)
{
    std::vector<std::string> out;
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
    return out;
}

double Neighbor::EuclidianDistance(QPoint point1, QPoint point2)
{
    return qSqrt(((point1.x() - point2.x())*(point1.x() - point2.x())) + ((point1.y() - point2.y())*(point1.y() - point2.y())));
}

double Neighbor::EuclidianDistanceWeight(QPoint point1, QPoint point2)
{
    double dist = qSqrt(((point1.x() - point2.x())*(point1.x() - point2.x())) + ((point1.y() - point2.y())*(point1.y() - point2.y())));
    return 1/(dist*dist);
}

QColor Neighbor::GetColor(int poz)
{
    for(size_t i=0;i< points.size()-1;i++)
        for(size_t j=i+1;j< points.size();j++)
        {
            if(i!=poz && j!=poz)
            {
                if(EuclidianDistance(points[i].GetPoint(), points[poz].GetPoint()) > EuclidianDistance(points[j].GetPoint(), points[poz].GetPoint()))
                {
                    auto p = points[i];
                    auto q = points[j];
                    points[i] = q;
                    points[j] = p;
                }
            }
        }
    int nrR = 0;
    int nrG = 0;
    for(int i=0; i<k; i++)
    {
        if(points[i].GetColor() == QColor(255, 0, 0))
            nrR++;
        else
            nrG++;
    }

    QColor c;
    if(nrR > nrG)
        return QColor(255, 0, 0);
    else
        return QColor(0, 0, 255);
}
