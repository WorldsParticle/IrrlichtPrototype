#pragma once

#include "generationstep.h"

namespace gen {

class TextureStep : public GenerationStep
{
public:

  ///
  /// \brief constructor
  ///
  TextureStep(const std::string &name);

  ///
  /// \brief destructor
  ///
  virtual ~TextureStep();

  ///
  /// \brief run
  ///
  virtual void    run();

  void paintTextureGrid();

private:


};

}
