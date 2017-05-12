#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>
#include <windows.h>

struct Config
{
	int video_file_input = 0;
	int console = 0;
	int save_video = 1;
	int record_video = 0;
	int batting_trajectories = 0;
	int batting_animation = 0;
	int images = 0;
	int foreground = 0;
	int pitching_trajectories = 0;
	int pitching_animation = 0;
};
//Function declarations
Config read_config(const char file[]);

void read_device_numbers(const char file_in_device_numbers[], int &camT, int &camR, int &camL);

void read_camera_constants(const char dir_camera_data[], float &k, int &width, int &height);

int main()
{
	char directory[256];
	char file_in_device_numbers[] = "DeviceNumbers.txt";
	char dir_camera_data[] = "";
	Config config = read_config("HomeDetectionConfig.txt");
	if (!config.console) ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (config.video_file_input)
	{
		/*int video_number;
		std::ifstream fin("video_file.txt");
		fin.getline(directory, 256);
		fin >> video_number;
		fin.close();
		sprintf(file_in_videoT, "%s\\video%03d_T.vid", directory, video_number);
		sprintf(file_in_videoR, "%s\\video%03d_R.vid", directory, video_number);
		sprintf(file_in_videoL, "%s\\video%03d_L.vid", directory, video_number);*/
		int video_number;
		std::ifstream fin("video_file.txt");
		fin.getline(directory, 256);
		fin >> video_number;
		fin.close();
		std::cout << "initialize Read from recorded vodeo file\n";
	}
	else
	{
		//sprintf(directory, "C:\\SensorData");
		std::cout << "initialize Read from camera\n";
	}


	// read camera parameters

	int rows, cols;
	float camera_k;
	read_camera_constants(dir_camera_data, camera_k, cols, rows);

	if (config.video_file_input)
	{
		/*video_readerT.open(VideoReader::SIMPLE_FILE, file_in_videoT);
		video_readerR.open(VideoReader::SIMPLE_FILE, file_in_videoR);
		video_readerL.open(VideoReader::SIMPLE_FILE, file_in_videoL);*/
		std::cout << "Read from recorded vodeo file\n";
	}
	else
	{
		int camT, camR, camL;
		read_device_numbers(file_in_device_numbers, camT, camR, camL);
		/*video_readerT.open(VideoReader::STANDARD, camT, cols, rows, 0, 0, 0, 0);
		video_readerR.open(VideoReader::STANDARD, camR, cols, rows, 0, 0, 0, 0);
		video_readerL.open(VideoReader::STANDARD, camL, cols, rows, 0, 0, 0, 0);*/
		std::cout << "Read from camera\n";
	}

	if (config.save_video)
	{
		/*CreateDirectoryA("D:\\SensorData\\Video", NULL);
		save_directory = "D:\\SensorData\\Video\\" + std::string(timestr);
		if (config.save_video == 1) save_directory += "_canceled";
		if (config.save_video == 2) save_directory += "_all";
		strcpy(inter_sensor_info.video_directory, save_directory.c_str());
		create_save_directory(save_directory, directory, dir_camera_data, file_in_common_config, file_in_strike_centerd,
			file_in_backgroundT, file_in_backgroundR, file_in_backgroundL,
			file_in_room_maskT, file_in_room_maskR, file_in_room_maskL,
			file_in_reflectionT, file_in_reflectionR, file_in_reflectionL,
			file_in_strike_maskT, file_in_strike_maskR, file_in_strike_maskL,
			file_in_referencesT, file_in_referencesR, file_in_referencesL,
			file_in_screen_maskT, file_in_screen_maskR, file_in_screen_maskL);
		fout.open(save_directory + "\\log_home_detection.txt");
		fout.precision(2);*/
		std::cout << "creates directory to save video\n";
	}

	if (config.record_video)
	{
		/*video_recorderT.open(0, rows, cols);
		video_recorderS.open(1, rows, cols);*/
		std::cout << "starts to record video\n";
	}

	return 0;
}

Config read_config(const char file[])
{
	Config c;

	std::ifstream fin(file);

	if (fin.fail()) return c;

	std::string name;
	int value;

	while (!fin.eof())
	{
		fin >> name >> value;

		if (name == "video_file_input")      c.video_file_input = value;
		else if (name == "console")               c.console = value;
		else if (name == "save_video")            c.save_video = value;
		else if (name == "record_video")          c.record_video = value;
		else if (name == "batting_trajectories")  c.batting_trajectories = value;
		else if (name == "batting_animation")     c.batting_animation = value;
		else if (name == "images")                c.images = value;
		else if (name == "foreground")            c.foreground = value;
		else if (name == "pitching_trajectories") c.pitching_trajectories = value;
		else if (name == "pitching_animation")    c.pitching_animation = value;
	}

	fin.close();

	return c;
}

void read_device_numbers(const char file_in_device_numbers[], int &camT, int &camR, int &camL)
{
	std::ifstream fin(file_in_device_numbers);

	if (fin.fail())
	{
		std::cerr << "Error: " << file_in_device_numbers << " not found.\n";
		exit(EXIT_FAILURE);
	}

	fin >> camT >> camT >> camT >> camR >> camL;

	fin.close();
}

void read_camera_constants(const char dir_camera_data[], float &k, int &width, int &height)
{
	//char pathname[256];
	char pathname[] = "camera_constants.txt";
	//sprintf_s(pathname, "%s\\camera_constants.txt", dir_camera_data);

	std::ifstream fin(pathname);

	if (fin.fail())
	{
		std::cerr << "Error: " << pathname << " does not exist.\n";
		exit(EXIT_FAILURE);
	}

	fin >> k >> width >> height;

	fin.close();
}