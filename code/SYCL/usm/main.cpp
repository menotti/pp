#include <iostream>
#include <sycl/sycl.hpp>

class vector_addition;

int main(int, char**) {
   auto device_selector{sycl::default_selector_v};

   sycl::queue queue(device_selector);
   std::cout << "Running on "
             << queue.get_device().get_info<sycl::info::device::name>() << "\n";

   auto a = sycl::malloc_shared<sycl::float4>(1, queue);
   auto b = sycl::malloc_shared<sycl::float4>(1, queue);
   auto c = sycl::malloc_shared<sycl::float4>(1, queue);

   a[0] = {1.1, 2.2, 3.3, 4.4};
   b[0] = {4.4, 3.3, 2.2, 1.1};
   c[0] = {0.0, 0.0, 0.0, 0.0};

   queue.parallel_for(4, [=](auto i) { 
      c[i] = a[i] + b[i]; 
   }).wait();

   std::cout << "  A { " << a->x() << ", " << a->y() << ", " << a->z() << ", " << a->w() << " }\n"
             << "+ B { " << b->x() << ", " << b->y() << ", " << b->z() << ", " << b->w() << " }\n"
             << "------------------\n"
             << "= C { " << c->x() << ", " << c->y() << ", " << c->z() << ", " << c->w() << " }"
             << std::endl;
   return 0;
}
