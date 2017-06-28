#include <vector>
#include <list>
#include <random>
#include <iostream>
#include <iterator>
#include <math.h>
/* Initialize segment
While iterations < num_of_iterations and segments_length > min_length:
	For each segment:
		Compute midpoint
		Displace midpoint
		Update segments
        Reduce displacement bounds
        iterations+1
*/
std::vector<std::pair<double, double>> midpointDisplacement(int width, int height, double roughness, int passes, double range)
{
	double lo = height/2;
	double hi = range;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dis(lo, hi);

	std::vector<std::pair<double, double>> ret;

	std::list<double> x{ 0, double(width) };
	std::list<double> y{double(dis(mt)), double(dis(mt))};
	// number of iterations
	for (int i = 0; i < passes; i++)
	{
		std::list<double>::iterator j, k;
		std::list<double>::iterator nexty, prevy;
		
		for (j = x.begin(), k = std::next(j,1), nexty=std::next(y.begin(),1), prevy = std::next(nexty, -1); k != x.end(); k++, nexty++)
		{
			// calculate displacement
			std::cout << "hi = " << hi << std::endl;
			std::cout << "lo = " << lo << std::endl;
			double midpoint = (*j / 2.0) + (*k / 2.0);
			x.insert(k, midpoint);
			y.insert(nexty, dis(mt));
			std::cout << "lo = " << lo << std::endl;
			std::cout << "hi = " << hi << std::endl;
			std::cout << "pass = " << i << std::endl;
		}
		// reduce displacement range
		range *= roughness;
		lo -= pow(2, -roughness);
		hi += lo + pow(2, -roughness);
		j = k;
		prevy = nexty;
		dis.param(std::uniform_real_distribution<>::param_type(lo, hi));

		std::cout << "hi = " << hi << std::endl;
		std::cout << "lo = " << lo << std::endl;
	}
	std::list<double>::iterator i;
	std::list<double>::iterator j;
	for (std::pair<std::list<double>::iterator, std::list<double>::iterator> i(x.begin(), y.begin());
		i.first != x.end() && i.second != y.end(); ++i.first, ++i.second)
	{
		std::cout << "Coords: " << *i.first << " " << *i.second << std::endl;
		ret.push_back(std::make_pair(*i.first, *i.second));
	}
	return ret;
}