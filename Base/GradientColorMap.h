#pragma once

#if defined(GradientColorMap_RECURSES)
#error Recursive header files inclusion detected in GradientColorMap.h
#else // defined(GradientColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GradientColorMap_RECURSES

#if !defined GradientColorMap_h
/** Prevents repeated inclusion of headers. */
#define GradientColorMap_h

#include <iostream>
#include "Base/Color.hpp"

namespace FEVV {

/**
 * class GradientColorMap
 * \brief This templated class may be used to (linearly) convert scalar
 * values in a given range into a color in a gradient defined by two
 * or more colors.
 *
 * The GradientColorMap can be used either as a functor object
 * (the value range is given at the object's construction, together with the
 * reference color) which converts a value into a Color structure,
 * or it can be used through a static method taking both the range and the
 * value as parameters.
 *
 * The code below shows a possible use of this class.
 * @code
 * #include <iostream>
 * #include "Base/Color.hpp"
 * #include "Base/GradientColorMap.h"
 *
 * using namespace FEVV;
 * // ...
 * {
 *
 *   GradientColorMap<float> gradient( 0.0, 1000.0, Color::White(), Color::Red() );
 *
 *   Color c = gradient( 230.0 );
 *   std::cout << "Color: [" << c.red()   << ";"
 *                           << c.green() << ";"
 *                           << c.blue()  << "]" << std::endl;
 * }
 * @endcode
 *
 * @tparam   PValue  The type of the range values.
 *
 *
 * \note This class has been ported from DGtal library
 * (http://dgtal.org - GNU LGPL v3).
 * Original author: Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et Instrumentation de
 * Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 */
template< typename PValue >
class GradientColorMap
{

public:
  using Value = PValue;

  /**
   * Constructor.
   */
  GradientColorMap() = delete;

  /**
   * Constructor.
   *
   * @pre      _min and _max values must be different. min < max.
   * @param    _min        The lower bound of the value range.
   * @param    _max        The upper bound of the value range.
   * @param    _firstColor The "left" color of the gradient.
   * @param    _lastColor  The "right" color of the gradient.
   */
  GradientColorMap(const Value &_min,
                   const Value &_max,
                   const Color &_firstColor,
                   const Color &_lastColor);

  /**
   * Copy constructor.
   *
   * @param    _other  The object to clone.
   */
  GradientColorMap(const GradientColorMap &_other);

  /**
   * Destructor.
   */
  ~GradientColorMap() = default;


  /**
   * Computes the color associated with a value in a given range.
   *
   * @param    _value  A value within the value range.
   * @return           A color whose brightness linearly depends on the
   *                   position of [_value] within the current range.
   */
  Color operator()(const Value &_value) const;

  /**
   * Assignment.
   *
   * @param    _other  The object to copy.
   * @return           A reference on 'this'.
   */
  GradientColorMap &operator=(const GradientColorMap &_other);

  /**
   * Adds a color to the list of color steps.
   *
   * @param    _color  A color.
   */
  void addColor(const Color &_color);

  /**
   * Clears the list of colors.
   *
   */
  void clear();

  /**
   * Returns the lower bound of the value range.
   *
   * @return           The lower bound of the value range.
   */
  const Value &minValue() const;

  /**
   * Returns the upper bound of the value range.
   *
   * @return           The upper bound of the value range.
   */
  const Value &maxValue() const;

  /**
   * Computes the color associated with a value in a given range.
   *
   * @pre      _min and _max values must be different. _min < _max.
   * @param    _colors The gradients boundary colors.
   * @param    _min    The lower bound of the value range.
   * @param    _max    The upper bound of the value range.
   * @param    _value  A value within the value range.
   * @return           A color whose color linearly depends on the
   *                   position of [_value] within the range
   *                   [_min]..[_max].
   */
  static Color getColor(const std::vector< Color > &_colors,
                        const Value &_min,
                        const Value &_max,
                        const Value &_value);

protected:
  Value myMin;                   /**< The lower bound of the value range.  */
  Value myMax;                   /**< The upper bound of the value range.  */
  std::vector< Color > myColors; /**< The gradients boundary colors. */
};
} // namespace FEVV


#include "Base/GradientColorMap.inl"


#endif // !defined GradientColorMap_h

#undef GradientColorMap_RECURSES
#endif // else defined(GradientColorMap_RECURSES)
