/*
 * ofGstUtils.h
 *
 *  Created on: 06-jun-2009
 *      Author: art
 */

#ifndef OFGSTUTILS_H_
#define OFGSTUTILS_H_

#include <gst/gst.h>
extern "C" {
#include <pthread.h>
}
#include "ofConstants.h"

typedef struct{
	GMainLoop 		*	loop;
	GstElement 		*	pipeline;
	unsigned char 	*	pixels;				// 24 bit: rgb
	pthread_mutex_t 	buffer_mutex;
	bool				bHavePixelsChanged;

	guint64				durationNanos;
	guint64				nFrames;
	int					pipelineState;
	float				speed;
}ofGstVideoData;

typedef struct
{
  int numerator;
  int denominator;
} ofGstFramerate;

typedef struct
{
  char *mimetype;
  int   width;
  int   height;
  int   num_framerates;
  ofGstFramerate *framerates;
  ofGstFramerate highest_framerate;
} ofGstVideoFormat;

typedef struct
{
  char *video_device;
  char *hal_udi;
  char *gstreamer_src;
  char *product_name;
  int   num_video_formats;
  vector<ofGstVideoFormat*> video_formats;

  /* Hash table for resolution based lookup of video_formats */
  GHashTable *supported_resolutions;
  ofGstVideoFormat * current_format;
} ofGstDevice;




typedef struct
{
  int num_webcam_devices;
  char *device_name;
  ofGstDevice *webcam_devices;
  int x_resolution;
  int y_resolution;
  int selected_device;

  guint eos_timeout_id;
  bool bInited;
} ofGstCamData;

class ofGstUtils {
public:
	ofGstUtils();
	virtual ~ofGstUtils();

	bool loadMovie(string uri);

	void listDevices();
	void setDeviceID(int id);
	bool initGrabber(int w, int h);

	bool setPipeline(string pipeline);
	bool setPipelineWithSink(string pipeline);

	bool isFrameNew();
	unsigned char * getPixels();
	void update();

	void play();
	void setPaused(bool bPause);

	int	getCurrentFrame();
	int	getTotalNumFrames();

	void firstFrame();
	void nextFrame();
	void previousFrame();

	int getHeight();
	int getWidth();

	float getPosition();
	float getSpeed();
	float getDuration();
	bool  getIsMovieDone();

	void setPosition(float pct);
	void setVolume(int volume);
	void setLoopState(int state);
	void setSpeed(float speed);
	void setFrame(int frame);  // frame 0 = first frame...

	void close();

protected:
	void                seek_lock();
	void                seek_unlock();
	void 				gstHandleMessage();
	bool 				allocate();
	bool				startPipeline();
	ofGstVideoFormat*	selectFormat(int w, int h);

	bool 				bStarted;
	bool 				bPlaying;
	bool 				bPaused;
	bool 				bIsFrameNew;			// if we are new
	bool				bIsMovieDone;
	int					loopMode;

	ofGstVideoData 		gstData;
	ofGstCamData		camData;

	bool				bIsStream;
	bool				bIsCamera;
	bool				bIsCustomWithSink;

	GstElement  *		gstSink;
	GstElement 	*		gstPipeline;


	bool				posChangingPaused;

	int 				width, height;
	bool 				bLoaded;
	//bool				allocated;				// so we know to free pixels or not

	pthread_mutex_t 	seek_mutex;


	// common with gstdata
	unsigned char 	*	pixels;				// 24 bit: rgb
	bool				bHavePixelsChanged;

	gint64				durationNanos;
	guint64				nFrames;
	int					pipelineState;
	float				speed;

	//camera only
	int					deviceID;

};

#endif /* OFGSTUTILS_H_ */
