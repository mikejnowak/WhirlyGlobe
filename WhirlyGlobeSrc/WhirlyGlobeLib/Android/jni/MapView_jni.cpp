/*
 * MapView_jni.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: sjg
 */


#import <jni.h>
#import "handle.h"
#import "com_mousebirdconsulting_maply_MapView.h"
#import "com_mousebirdconsulting_maply_Point3d.h"
#import "com_mousebirdconsulting_maply_Matrix4d.h"
#import "WhirlyGlobe.h"

using namespace Eigen;
using namespace WhirlyKit;

JNIEXPORT void JNICALL Java_com_mousebirdconsulting_maply_MapView_initialise
  (JNIEnv *env, jobject obj, jobject coordAdapterObj)
{
	try
	{
		CoordSystemDisplayAdapter *coordAdapter = getHandle<CoordSystemDisplayAdapter>(env,coordAdapterObj);
		Maply::MapView *inst = new Maply::MapView(coordAdapter);
		setHandle(env,obj,inst);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::initialise()");
	}
}

JNIEXPORT void JNICALL Java_com_mousebirdconsulting_maply_MapView_dispose
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *inst = getHandle<Maply::MapView>(env,obj);
		if (!inst)
			return;
		delete inst;

		clearHandle(env,obj);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::dispose()");
	}
}

JNIEXPORT void JNICALL Java_com_mousebirdconsulting_maply_MapView_setLoc
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return;

		view->setLoc(Point3d(x,y,z));
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::setLoc()");
	}
}

JNIEXPORT jobject JNICALL Java_com_mousebirdconsulting_maply_MapView_getLoc
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return NULL;

		Point3d pt = view->getLoc();

		return MakePoint3d(env,pt);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::getLoc()");
	}

	return NULL;
}

JNIEXPORT jdouble JNICALL Java_com_mousebirdconsulting_maply_MapView_minHeightAboveSurface
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return 0.0;

		return view->minHeightAboveSurface();
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::minHeightAboveSurface()");
	}
}

JNIEXPORT jdouble JNICALL Java_com_mousebirdconsulting_maply_MapView_maxHeightAboveSurface
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return 0.0;

		return view->maxHeightAboveSurface();
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::maxHeightAboveSurface()");
	}
}


JNIEXPORT void JNICALL Java_com_mousebirdconsulting_maply_MapView_setRot
  (JNIEnv *env, jobject obj, jdouble rot)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return;

		view->setRotAngle(rot);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::setRot()");
	}
}


JNIEXPORT jdouble JNICALL Java_com_mousebirdconsulting_maply_MapView_getRot
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return 0.0;

		return view->getRotAngle();
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::getRot()");
	}
}

JNIEXPORT void JNICALL Java_com_mousebirdconsulting_maply_MapView_runViewUpdates
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return;
		view->runViewUpdates();
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::runViewUpdates()");
	}
}

JNIEXPORT jobject JNICALL Java_com_mousebirdconsulting_maply_MapView_calcModelViewMatrix
  (JNIEnv *env, jobject obj)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return NULL;

		Matrix4d mat = view->calcModelMatrix();
		return MakeMatrix4d(env,mat);
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::calcModelViewMatrix()");
	}
}

JNIEXPORT jobject JNICALL Java_com_mousebirdconsulting_maply_MapView_pointOnPlaneFromScreen
  (JNIEnv *env, jobject obj, jobject screenPtObj, jobject viewModelMatObj, jobject frameObj, jboolean clip)
{
	try
	{
		Maply::MapView *view = getHandle<Maply::MapView>(env,obj);
		if (!view)
			return NULL;
		Point2d *screenPt = getHandle<Point2d>(env,screenPtObj);
		Matrix4d *viewModelMat = getHandle<Matrix4d>(env,viewModelMatObj);
		Point2d *framePt = getHandle<Point2d>(env,frameObj);
		Point3d hit;

		Point2f screenPt2f(screenPt->x(),screenPt->y());
		Point2f framePt2f(framePt->x(),framePt->y());
		if (view->pointOnPlaneFromScreen(screenPt2f,viewModelMat,framePt2f,&hit,clip))
		{
			return MakePoint3d(env,hit);
		} else
			return NULL;
	}
	catch (...)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapView::pointOnPlaneFromScreen()");
	}
}
