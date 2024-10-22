#pragma once

// some of these to eventually go in an options menu or something?

namespace constants {

inline const std::filesystem::path fontPath{"data/Play-Regular.ttf"};

inline constexpr int titleScreenTitleFontSize{72};
inline constexpr int titleScreenInstructionFontSize{36};
inline constexpr double titleScreenPadding{150.0};

inline constexpr int initialNumOfAsteroids{3};
inline constexpr double initialAsteroidScale{3.0};
inline constexpr int mainLevelScoreboardXPos{17};
inline constexpr int mainLevelscoreboardYPos{10};
inline constexpr int mainLevelScoreboardFontSize{28};
inline constexpr double fluidDensity{0.1};

inline constexpr int gameOverTitleFontSize{72};
inline constexpr int gameOverScoreFontSize{48};
inline constexpr double gameOverPadding{250.0};

inline constexpr int highScoresTitleFontSize{64};
inline constexpr int highScoresScoreFontSize{36};
inline constexpr double highScoresInternPadding{25.0};
inline constexpr double highScoresExternPadding{25.0};
inline const std::filesystem::path highScoresPath{"data/highScores"};
inline constexpr size_t maxHighScores{5};

inline constexpr double bulletMass{0.003};
inline constexpr double bulletScale{1.0};
inline constexpr double bulletLifespan{1.0};  // seconds
inline const std::vector<utl::Vec2d> bulletShape{
    {1, -3}, {-1, -3}, {-2, 3}, {2, 3}};

inline const double asteroidMass{1.0};
inline constexpr double asteroidRadiusMin = 25.0;
inline constexpr double asteroidRadiusMax = 30.0;
inline constexpr double asteroidImpulseMin{750'000.0};
inline constexpr double asteroidImpulseMax{1'500'000.0};
inline constexpr int minAsteroidVertices{8};
inline constexpr int maxAsteroidVertices{10};

inline const std::vector<utl::Vec2d> enemyShape{
    {0, -30},   // top
    {15, -10},  // top right
    {20, 30},   // bottom right
    {0, 15},    // bottom
    {-20, 30},  // bottom right
    {-15, -10}  // top left
};
inline constexpr double enemyScale{1.0};
inline constexpr double enemyPower{5000.0};
inline constexpr double enemyTurnSpeed{300.0};
inline constexpr double enemyMinVel{150.0};
inline constexpr double enemyMaxVel{300.0};
inline constexpr double enemyShotPower{20000.0};
inline constexpr double enemyMass{0.1};
inline constexpr double enemyCooldown{1.0};
inline constexpr double enemyDistance{75.0};

inline const std::vector<utl::Vec2d> playerShape{{0, -30}, {20, 30}, {-20, 30}};
inline constexpr double playerScale{1.0};
inline constexpr double playerEnginePower{5000.0};
inline constexpr double playerTurnSpeed{300.0};
inline constexpr double playerShotPower{20000.0};
inline constexpr double playerMass{0.1};
inline constexpr double playerWarpLength{1.0};
inline constexpr int playerLives{3};
inline constexpr double playerRespawnLength{2.0};
inline constexpr double playerFlashLength{0.2};
inline constexpr double playerGunCooldown{0.25};

}  // namespace constants
