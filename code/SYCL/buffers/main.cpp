#include <iostream>
#include <sycl/sycl.hpp>

class vector_addition;

int main(int, char**) {
   sycl::float4 a = { 1.1, 2.2, 3.3, 4.4 };
   sycl::float4 b = { 4.4, 3.3, 2.2, 1.1 };
   sycl::float4 c = { 0.0, 0.0, 0.0, 0.0 };

   auto device_selector{sycl::default_selector_v};

   sycl::queue queue(device_selector);
   std::cout << "Running on "
             << queue.get_device().get_info<sycl::info::device::name>() << "\n";
   {
      sycl::buffer<sycl::float4, 1> a_sycl(&a, sycl::range<1>(1));
      sycl::buffer<sycl::float4, 1> b_sycl(&b, sycl::range<1>(1));
      sycl::buffer<sycl::float4, 1> c_sycl(&c, sycl::range<1>(1));
  
      queue.submit([&] (sycl::handler& cgh) {
         auto a_acc = a_sycl.get_access<sycl::access::mode::read>(cgh);
         auto b_acc = b_sycl.get_access<sycl::access::mode::read>(cgh);
         auto c_acc = c_sycl.get_access<sycl::access::mode::discard_write>(cgh);

         cgh.single_task<class vector_addition>([=] () {
         c_acc[0] = a_acc[0] + b_acc[0];
         });
      });
   }
   std::cout << "  A { " << a.x() << ", " << a.y() << ", " << a.z() << ", " << a.w() << " }\n"
             << "+ B { " << b.x() << ", " << b.y() << ", " << b.z() << ", " << b.w() << " }\n"
             << "------------------\n"
             << "= C { " << c.x() << ", " << c.y() << ", " << c.z() << ", " << c.w() << " }"
             << std::endl;
   return 0;
}
