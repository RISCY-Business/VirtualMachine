#include "../virtualMachineInterface/computor.h"
#include "../library/include/asserts.h"
#include "../library/include/filesystem.h"

int main(int ARGUMENT_COUNT, char* ARGUMENT_VECTOR[]) 
{
  FORGE_ASSERT_MESSAGE(ARGUMENT_COUNT == 2, "Usage: ./vm <filepath>");
  const char* filepath = ARGUMENT_VECTOR[1];
  FORGE_ASSERT_MESSAGE(fileExists(filepath), "The file path must exist");

  startComputor();
  loadProgram(filepath);

  for (int i = 0; i < 30; ++i)
  {
    update();
  }

  stopComputor();
}
