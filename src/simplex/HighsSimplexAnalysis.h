/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file simplex/HighsSimplexAnalysis.h
 * @brief Analyse simplex iterations, both for run-time control and data gathering
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef SIMPLEX_HIGHSSIMPLEXANALYSIS_H_
#define SIMPLEX_HIGHSSIMPLEXANALYSIS_H_

//#include <vector>

#include <cstdio>
#include <string>
#include "HConfig.h"
#include "SimplexConst.h"
//#include "HSimplex.h"
//#include "simplex/HVector.h"

#ifdef HiGHSDEV
  enum ANALYSIS_OPERATION_TYPE {
    ANALYSIS_OPERATION_TYPE_BTRAN = 0,
    ANALYSIS_OPERATION_TYPE_PRICE,
    ANALYSIS_OPERATION_TYPE_FTRAN,
    ANALYSIS_OPERATION_TYPE_FTRAN_BFRT,
    ANALYSIS_OPERATION_TYPE_FTRAN_DSE,
    NUM_ANALYSIS_OPERATION_TYPE,
  };
#endif

/**
 * @brief Analyse simplex iterations, both for run-time control and data gathering
 */
class HighsSimplexAnalysis {
 public:
  void setup(int numCol_,            //!< Number of columns
             int numRow_            //!< Number of rows
	     );

  void updateOperationResultDensity(const double local_density,
				    double& density
				    );

  void equalDensity(const double density0, const double density1);

  /*
  void iterationAnalysisInitialise();
  void iterationAnalysis();
#ifdef HiGHSDEV
  void iterateOpRecBf(int opTy, HVector& vector, double hist_dsty);
  void iterateOpRecAf(int opTy, HVector& vector);
  void iterationAnalysisReport();
#endif
  */

  int numRow;
  int numCol;
  const double running_average_multiplier = 0.05;
  double col_aq_density;
  double row_ep_density;
  double row_ap_density;
  double row_DSE_density;
  
 private:
  int AnIterIt0;
#ifdef HiGHSDEV
  int AnIterPrevIt;
  // Major operation analysis struct
  struct AnIterOpRec {
    double AnIterOpLog10RsDsty;
    double AnIterOpSuLog10RsDsty;
    double AnIterOpHyperCANCEL;
    double AnIterOpHyperTRAN;
    int AnIterOpRsDim;
    int AnIterOpNumCa;
    int AnIterOpNumHyperOp;
    int AnIterOpNumHyperRs;
    int AnIterOpRsMxNNZ;
    int AnIterOpSuNumCa;
    int AnIterOpSuNumHyperOp;
    int AnIterOpSuNumHyperRs;
    std::string AnIterOpName;
  };
  AnIterOpRec AnIterOp[NUM_ANALYSIS_OPERATION_TYPE];

  struct AnIterTraceRec {
    double AnIterTraceTime;
    double AnIterTraceDsty[NUM_ANALYSIS_OPERATION_TYPE];
    double AnIterTraceAux0;
    int AnIterTraceIter;
    int AnIterTrace_dual_edge_weight_mode;
  };

  enum AnIterTraceMxNumRec { AN_ITER_TRACE_MX_NUM_REC = 20 };
  enum DUAL_EDGE_WEIGHT_MODE_COUNT { DUAL_EDGE_WEIGHT_MODE_COUNT = 3 };
  int AnIterTraceNumRec;
  int AnIterTraceIterDl;
  AnIterTraceRec AnIterTrace[1 + AN_ITER_TRACE_MX_NUM_REC + 1];

  int AnIterNumInvert[INVERT_HINT_Count];
  int AnIterNumColPrice;
  int AnIterNumRowPrice;
  int AnIterNumRowPriceWSw;
  int AnIterNumRowPriceUltra;
  int AnIterNumPrDgnIt;
  int AnIterNumDuDgnIt;
  int AnIterNumEdWtIt[(int)DualEdgeWeightMode::Count];
#endif
};

#endif /* SIMPLEX_HIGHSSIMPLEXANALYSIS_H_ */
