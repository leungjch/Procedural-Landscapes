// Example program
#include <iostream>
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
/*
Initialize segment
While iterations < num_of_iterations and segments_length > min_length:
For each segment:
Compute midpoint
Displace midpoint
Update segments
Reduce displacement bounds
iterations+1
*/


std::vector<std::pair<double, double> > midpointDisplacement(int width, int height, double roughness, int totPasses, double range)
{
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> gen(height/2, height);
	std::uniform_real_distribution<double> between_range(0, range);
	std::uniform_real_distribution<double> zero_to_one(0.0, 1.0);

	std::vector<std::pair<double, double> > ret{ std::make_pair(0,gen(rng)), std::make_pair(width,gen(rng)) };

	// iterate through number of passes
	for (int pass = 1; pass <= totPasses; pass++)
	{
		// iterate through width of screen (there are 2^passes + 1 of points)
		std::cout << "pow is " << pow(2, pass) << std::endl;
		int prev;
		int cur;
		for (cur = 0, prev = 0; cur < pow(2, pass); cur = cur + 2, prev++)
		{
			// calculate midpoint by taking the average of the current and next x value
			double midpoint = (ret[cur].first + ret[cur + 1].first) / 2.0;
			double yPoint = 0;

			double rand = zero_to_one(rng);
			if ((rand < 0.50) && (((ret[cur].second + ret[cur + 1].second) / 2 + range) < height))
			{
				yPoint = (ret[cur].second + ret[cur + 1].second)/2 + range;
				std::cout << "Current yPoint is " << yPoint << std::endl;
			}
			else
			{
				yPoint = (ret[cur].second + ret[cur + 1].second) / 2 - range;
				std::cout << "Current yPoint is " << yPoint << std::endl;
			}
			// insert the point into return vector
			ret.insert(ret.begin() + cur + 1, std::make_pair(midpoint, yPoint));

			// reduce the range
		}
		range *= pow(2, -roughness);
		int i;
		int j;
		for (i = 0, j = 1; j < ret.size(); ++i, ++j)
		{
			std::cout << "X: " << ret[i].first << " " << "Y: " << ret[i].second << " : " << ret[i].second - ret[j].second << std::endl;
		}

	}
	return ret;
}