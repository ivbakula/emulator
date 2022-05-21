#include "Core.hxx"
#include "PeripherialBus.hxx"

int main() {
  ExternalLayer::ExternalBus external;
  Core core(&external);

  core.run();
}
