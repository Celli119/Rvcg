#include <../typedef.h>
#include <../RvcgIO.h>
#include <Rcpp.h>
#include <vcg/complex/algorithms/point_sampling.h>
#include <vcg/complex/algorithms/point_sampling.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <vcg/complex/algorithms/clustering.h>
#include <vcg/simplex/face/distance.h>
#include <vcg/complex/algorithms/geodesic.h>
using namespace vcg;
using namespace tri;
using namespace Rcpp;
using namespace std;


RcppExport SEXP Rsample(SEXP _vb, SEXP _it, SEXP _SampleNum, SEXP _type, SEXP _MCsamp, SEXP _geodes)
{
  // declare Mesh and helper variables
  int SampleNum = Rcpp::as<int>(_SampleNum);  
  //double tol = Rcpp::as<double>(_tol);  
  const int type = Rcpp::as<int>(_type);  
  const int MCsamp = Rcpp::as<int>(_MCsamp);
  const bool geodes = Rcpp::as<bool>(_geodes);
  int i, j;
  MyMesh m,msamp;
  float radius;
  VertexIterator vi;
  FaceIterator fi;
  // allocate mesh and fill it
  Rvcg::IOMesh<MyMesh>::RvcgReadR(m,_vb,_it);
  /*m.vert.EnableVFAdjacency();
  m.face.EnableFFAdjacency();
  m.face.EnableVFAdjacency();*/
  vector<Point3f> myVec;
  typedef TrivialSampler<MyMesh>  BaseSampler ;
 
  BaseSampler ts2(myVec);
  std::vector<Point3f> MontecarloSamples, poissonsamples;
  BaseSampler mcSampler(MontecarloSamples);
  BaseSampler pdSampler(poissonsamples);
  
  
   if (type == 1)
    tri::MontecarloSampling(m,poissonsamples,SampleNum);
   else
     { //this is poison disk sampling with more options than the wrapper commented below

       radius = tri::SurfaceSampling<MyMesh,BaseSampler>::ComputePoissonDiskRadius(m,SampleNum);
       tri::SurfaceSampling<MyMesh, BaseSampler>::PoissonDiskParam pp;
       tri::SurfaceSampling<MyMesh, BaseSampler>::PoissonDiskParam::Stat stat;
       pp.pds = &stat;
       pp.pds->sampleNum = SampleNum;
       pp.geodesicDistanceFlag=geodes;
       MyMesh MontecarloMesh;
       SurfaceSampling<MyMesh,BaseSampler>::Montecarlo(m, mcSampler, SampleNum*MCsamp);
   
       tri::Allocator<MyMesh>::AddVertices(MontecarloMesh,MontecarloSamples.size());
       for(size_t j=0;j < MontecarloSamples.size();++j)
	 MontecarloMesh.vert[j].P()=MontecarloSamples[j];
  
       tri::UpdateBounding<MyMesh>::Box(MontecarloMesh);
       tri::SurfaceSampling<MyMesh,BaseSampler>::PoissonDiskPruning(pdSampler, MontecarloMesh, radius, pp);
    }
  
  
  
 
  /* 
     else 
     {float radius=0;
    vcg::tri::PoissonSampling(m, poissonsamples, SampleNum, radius);
    }
  */
  
  size_t outsize = poissonsamples.size();
  Rcpp::NumericMatrix vbout(3,outsize);
  
  for (i=0;  i < outsize; i++) 
    {
      Point3f tmp = poissonsamples[i];
      vbout(0,i) = tmp[0];
      vbout(1,i) =  tmp[1];
      vbout(2,i) =  tmp[2];
    }
  	 
	  return Rcpp::wrap(vbout);
	  /*return Rcpp::List::create(Rcpp::Named("vb") = vbout,
			    Rcpp::Named("it") = itout,
			    Rcpp::Named("normals") = normals
			    );
	  */
}
 

    