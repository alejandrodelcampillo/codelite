#include "LSPClangdDetector.hpp"
#include "LSPDetectorManager.hpp"
#include "LSPPythonDetector.hpp"
#include "LSPRlsDetector.hpp"
#include "LSPRustAnalyzerDetector.hpp"
#include "LanguageServerConfig.h"
#include "LanguageServerEntry.h"
#include "file_logger.h"

LSPDetectorManager::LSPDetectorManager()
{
    m_detectors.push_back(LSPDetector::Ptr_t(new LSPClangdDetector()));
    m_detectors.push_back(LSPDetector::Ptr_t(new LSPPythonDetector()));
    m_detectors.push_back(LSPDetector::Ptr_t(new LSPRlsDetector()));
    m_detectors.push_back(LSPDetector::Ptr_t(new LSPRustAnalyzerDetector()));
}

LSPDetectorManager::~LSPDetectorManager() {}

size_t LSPDetectorManager::Scan(std::vector<LSPDetector::Ptr_t>& matchers)
{
    for(LSPDetector::Ptr_t detector : m_detectors) {
        clDEBUG() << "LSP detector: trying" << detector->GetName();
        if(detector->Locate()) {
            clDEBUG() << "  ==> " << detector->GetName() << "found";
            matchers.push_back(detector);
        }
    }
    return matchers.size();
}
