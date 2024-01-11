#include<digiPaper/digi_paper.hpp>


int main() {

	
	Space area(100);


	Space::Point3 a1(20, -100, 0);
	Space::Point3 a2(100, -10, 0);
	Space::Line2 fold = area.compute_line_points(a1, a2);
	double radius1 = area.compute_distance_to_line(Space::Point3(100, -100, 0), fold) / cPi;

	Space::Point3 c1(-100, 10, 0);
	Space::Point3 c2(-30, 100, 0);
	double radius3 = 60;

	area.cylindrical_bending(a1, a2, radius1);
	area.cylindrical_bending(c1, c2, radius3);

	std::ofstream output;
	output.open("output.txt");

	area.WriteTo(output);

	output.close();
	return 0;
}