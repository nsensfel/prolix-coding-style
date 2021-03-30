/**
 * Example of Prolix coding style, based on those available at
 * https://github.com/motine/cppstylelineup
 **/

#include <iostream>

namespace western
{
   enum class ShootingHand
   {
      LEFT,
      RIGHT
   };

   #define COWBOY_DEFAULT_AGE 45
   #define COWBOY_DEFAULT_AVAILABLE_BULLETS 2
   #define COWBOY_SHOOT_THRESHOLD_EXAMPLE 10

   class Cowboy
   {
      public:
         Cowboy ();
         Cowboy (const int available_bullets);
         ~Cowboy ();

         void shoot (const std::string target_name);

         int get_age () const
         {
            return age;
         }

      protected:
         void print_bangs (const int &number_of_bangs_to_print) const;

         int age;
         int available_bullets;
   };

   Cowboy::Cowboy ()
      :
         age (COWBOY_DEFAULT_AGE),
         available_bullets (COWBOY_DEFAULT_AVAILABLE_BULLETS)
   {
      std::cout << "I am alive!" << std::endl;
   }

   Cowboy::Cowboy (const int available_bullets)
      :
         age (COWBOY_DEFAULT_AGE),
         available_bullets (available_bullets)
   {
      // And this is the longest inline comment you have every seen. Lorem
      // Ipsum. Bacon! Cheese. Bread. Beer. Fish. Mobile fridge. More random
      // words come here...
      std::cout << "Howdy!" << std::endl;
   }

   Cowboy::~Cowboy ()
   {
      std::cout << "RIP" << std::endl;
   }

   void Cowboy::shoot ([[maybe_unused]] const std::string target_name)
   {
      age++;

      const int arbitrary_number {5 + (7 * 3)};

      print_bangs(arbitrary_number);

      if (arbitrary_number > COWBOY_SHOOT_THRESHOLD_EXAMPLE)
      {
         return;
      }

      switch (age)
      {
         case COWBOY_DEFAULT_AGE:
            age--;
            break;

         default:
            age++;
            break;
      }
   }

   void Cowboy::print_bangs (const int &number_of_bangs_to_print) const
   {
      for (int i = 0; i < number_of_bangs_to_print; ++i)
      {
         std::cout << "Bang!" << std::endl;
      }
   }

   void some_very_long_method
   (
      [[maybe_unused]] const int param1,
      [[maybe_unused]] const int param2,
      [[maybe_unused]] const int param3,
      [[maybe_unused]] const int param4,
      [[maybe_unused]] const int param5,
      [[maybe_unused]] const int param6,
      [[maybe_unused]] const int param7,
      [[maybe_unused]] const int param8,
      [[maybe_unused]] const int param9,
      [[maybe_unused]] const int param10
   )
   {
      std::cout << "So long..." << std::endl;
   }
}

using namespace western;

int main ()
{
   Cowboy amy;
   Cowboy angus (2);
   Cowboy *current_cowboy = &amy;

   current_cowboy->shoot("yourself");

   return 0;
}
