#include<digiPaper/digi_paper.hpp>

typedef long long ll;

Space::Point3::Point3(double xx, double yy, double zz, bool select) 
	: x(xx), y(yy), z(zz), is_selected(select) {}

Space::Point3::Point3() : Point3(0, 0, 0, false) {}

Space::Line2::Line2() :A(0), B(0), C(0) {}

Space::Line2::Line2(double a, double b, double c) :
	A(a), B(b), C(c) {}


Space::Point3 Space::compute_midpoint(Space::Point3 a1, Space::Point3 a2) {
	Space::Point3 res(0, 0, 0);
	res.x = (a1.x + a2.x) / 2.0;
	res.y = (a1.y + a2.y) / 2.0;
	res.z = (a1.z + a2.z) / 2.0;
	return res;
}

Space::CylindricalCoordinate::CylindricalCoordinate() :r(0), phi(0), z(0)
{
}

Space::CylindricalCoordinate::CylindricalCoordinate(double dist, double angle, double height) :
	r(dist), phi(angle), z(height)
{
}


Space::Line2 Space::compute_perpendicular_line(Space::Line2 line, Space::Point3 mid) {
	double A = line.B / line.A;
	double B = -1;
	double C = -1 * (A * mid.x + B * mid.y);
	return Space::Line2(A, B, C);
}

double Space::compute_distance_to_line(Space::Point3 m, Space::Line2 line) {
	return (line.A * m.x + line.B * m.y + line.C) / std::sqrt(std::pow(line.A, 2) + std::pow(line.B, 2));
}

Space::Line2 Space::compute_line_points(Point3 p1, Point3 p2) {
	Line2 line;

	line.A = p2.y - p1.y;
	line.B = p1.x - p2.x;
	line.C = (-1) * (line.A * p1.x + line.B * p1.y);

	return line;
}

bool Space::is_point_below_line(Point3 p, Line2 l) {
	double value = l.A * p.x + l.B * p.y + l.C;
	return value > 0;
}

double Space::calculate_angle_between_lines(const Eigen::Vector2d& line1, const Eigen::Vector2d& line2) {
	double dotProduct = line1.dot(line2);

	double lenLine1 = line1.norm();
	double lenLine2 = line2.norm();

	double cosTheta = dotProduct / (lenLine1 * lenLine2);

	return acos(cosTheta);
}

Space::CylindricalCoordinate Space::to_cylindr_coordinate(Point3 p, Line2 perp_line, double r, Line2 fold) {
	CylindricalCoordinate point;
	point.r = r;
	point.z = compute_distance_to_line(p, perp_line);
	double dist_to_fold = compute_distance_to_line(p, fold);
	point.phi = ((dist_to_fold / (cPi * r)) * cPi) - cPi / 2.0;
	return point;
}

Space::Point3 Space::cylindrical_to_cartesian(CylindricalCoordinate cylCoords, Point3 offset, double angle) {
	Point3 dec_cord(0, 0, 0);

	dec_cord.x = cylCoords.r * cos(cylCoords.phi);
	dec_cord.y = cylCoords.r * sin(cylCoords.phi);
	dec_cord.z = cylCoords.z;


	Eigen::AngleAxisd roll_z(0, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd roll_y(0, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd roll_x(cPi / 2, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = roll_x * roll_y * roll_z;

	Eigen::Matrix3d rotation_matrix_x = q.matrix();

	Eigen::AngleAxisd roll_z1(angle, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd roll_y1(0, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd roll_x1(0, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q1 = roll_x1 * roll_y1 * roll_z1;

	Eigen::Matrix3d rotation_matrix_z = q1.matrix();

	Eigen::Vector3d cartVector(dec_cord.x, dec_cord.y, dec_cord.z);

	Eigen::Vector3d rotatedVector = rotation_matrix_x * cartVector;
	rotatedVector = rotation_matrix_z * rotatedVector;

	dec_cord.x = rotatedVector(0) + offset.x;
	dec_cord.y = rotatedVector(1) + offset.y;
	dec_cord.z = rotatedVector(2) + offset.z;

	return dec_cord;
}

Space::Space() :Space(50) {}

Space::Space(ll dimension) :
	dim_(dimension), cube_(std::pow(dimension + 1, 3) - 1)
{
	surface.resize(cube_ * 8 + 50);
	for (ll z = -dim_; z <= dim_; z += 1) {
		for (ll y = -dim_; y <= dim_; y += 1) {
			for (ll x = -dim_; x <= dim_; x += 1) {
				ll position = cord_to_vec(x, y, z);
				surface[position] = Point3(x, y, z, false);
			}
		}
	}

	for (ll y = -dim_; y <= dim_; y += 1) {
		for (ll x = -dim_; x <= dim_; x += 1) {
			ll position = cord_to_vec(x, y, 0);
			surface[position] = Point3(x, y, 0, true);
		}
	}



}

Space::Point3 Space::round_cord(Point3 p) {
	double x = p.x;
	double y = p.y;
	double z = p.z;

	x = std::round(x);
	y = std::round(y);
	z = std::round(z);

	if (std::abs(x) > dim_ && x<1 && x>-1) x = x > 0 ? dim_ : -dim_;
	if (std::abs(y) > dim_ && y<1 && y>-1) y = y > 0 ? dim_ : -dim_;
	if (std::abs(z) > dim_ && z<1 && z>-1) z = z > 0 ? dim_ : -dim_;

	return Point3(x, y, z);
}


long long Space::cord_to_vec(double xx, double yy, double zz) {
	ll x = std::round(xx);
	ll y = std::round(yy);
	ll z = std::round(zz);

	ll position = std::abs(z) * std::pow(dim_, 2) + std::abs(y) * dim_ + std::abs(x);
	if (x == 0 && y == 0 && z == 0) return position;
	if (x >= 0 && y >= 0 && z <= 0) return cube_ * 0 + position;
	if (x <= 0 && y >= 0 && z <= 0) return cube_ * 1 + position;
	if (x <= 0 && y <= 0 && z <= 0) return cube_ * 2 + position;
	if (x >= 0 && y <= 0 && z <= 0) return cube_ * 3 + position;
	if (x >= 0 && y >= 0 && z >= 0) return cube_ * 4 + position;
	if (x <= 0 && y >= 0 && z >= 0) return cube_ * 5 + position;
	if (x <= 0 && y <= 0 && z >= 0) return cube_ * 6 + position;
	if (x >= 0 && y <= 0 && z >= 0) return cube_ * 7 + position;
}


Space::Point3 Space::vec_to_cord(ll num) {
	Point3 cord(0, 0, 0);

	cord = surface[num];

	return cord;

	/*ll option = num / cube_;
	num -= option * cube_;

	cord.z = num / std::pow(dim_, 2);
	num -= cord.z * std::pow(dim_, 2);
	cord.y = num / dim_;
	num -= cord.y * dim_;
	cord.x = num;

	switch (option) {
	case 0:
		cord.x *= 1;
		cord.y *= 1;
		cord.z *= -1;
		break;

	case 1:
		cord.x *= -1;
		cord.y *= 1;
		cord.z *= -1;
		break;

	case 2:
		cord.x *= -1;
		cord.y *= -1;
		cord.z *= -1;
		break;

	case 3:
		cord.x *= 1;
		cord.y *= -1;
		cord.z *= -1;
		break;

	case 4:
		cord.x *= 1;
		cord.y *= 1;
		cord.z *= 1;
		break;

	case 5:
		cord.x *= -1;
		cord.y *= 1;
		cord.z *= 1;
		break;

	case 6:
		cord.x *= -1;
		cord.y *= -1;
		cord.z *= 1;
		break;

	case 7:
	case 8:
		cord.x *= 1;
		cord.y *= -1;
		cord.z *= 1;
		break;
	}

	return cord;
	*/
}

bool Space::is_paper(ll x, ll y, ll z) {
	ll position = cord_to_vec(x, y, z);
	return surface[position].is_selected;
}

void Space::change_point(Point3 p, bool is_paper) {
	Point3 p1 = round_cord(p);
	ll x = p1.x;
	ll y = p1.y;
	ll z = p1.z;
	ll position = cord_to_vec(x, y, z);
	surface[position] = p;
	surface[position].is_selected = is_paper;
}

Space::Point3 Space::get_point(ll x, ll y, ll z) {
	ll position = cord_to_vec(x, y, z);
	Point3 p = surface[position];
	return p;
}

void Space::cylindrical_bending(Point3 a1, Point3 a2, double radius) {
	//a1 левее a2
	if (a1.x > a2.x) std::swap(a1, a2);

	Point3 midpoint = compute_midpoint(a1, a2);
	Line2 fold = compute_line_points(a1, a2);
	Line2 perp_line = compute_perpendicular_line(fold, midpoint);

	Eigen::Vector2d line1(fold.A, fold.B); //Fold
	Eigen::Vector2d line2(1, 0); //OX
	// Вычисление угла между прямыми
	double angle_turn = calculate_angle_between_lines(line1, line2);
	angle_turn *= -1;

	bool is_under_line = false;
	if (a1.y == (-dim_) || a2.y == -dim_) is_under_line = true;

	for (ll y = std::min(a1.y, a2.y); y <= std::max(a1.y, a2.y); y += 1) {
		for (ll x = a1.x; x <= a2.x; x += 1) {

			Point3 p = get_point(x, y, 0);

			if (!p.is_selected) continue;
			if (!is_point_below_line(p, fold) && is_under_line) continue;
			if (is_point_below_line(p, fold) && !is_under_line) continue;

			CylindricalCoordinate cylindr_coord = to_cylindr_coordinate(p, perp_line, radius, fold);
			Point3 cartesian_cord = cylindrical_to_cartesian(cylindr_coord, Point3(midpoint.x, midpoint.y, radius), angle_turn);
			change_point(p, false);
			change_point(cartesian_cord, true);

		}
	}

}

std::ostream& Space::WriteTo(std::ostream& ostrm) {
	for (ll z = -dim_; z < dim_; z += 1) {
		for (ll y = -dim_; y < dim_; y += 1) {
			for (ll x = -dim_; x < dim_; x += 1) {

				Point3 p = get_point(x, y, z);
				double dk = dim_;
				if (p.is_selected) {
					ostrm << std::fixed << std::setprecision(3) <<
						p.x / (dk) << " " << p.y / (dk) << " " << p.z / (dk) << std::endl;
				}
			}
		}
	}

	return ostrm;
}
