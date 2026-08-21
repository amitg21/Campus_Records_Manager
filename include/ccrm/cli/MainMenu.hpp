#pragma once

namespace ccrm::cli {

class MainMenu {
public:
    void run();

private:
    void dataUtilitiesFlow();
    void reportsFlow();
    void loadInitialData();
};

} // namespace ccrm::cli
