#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

constexpr unsigned MAX_SONG_TITLE_SIZE = 128;
constexpr unsigned MAX_SONG_ARTIST_SIZE = 64;
constexpr unsigned MAX_PLAYLIST_NAME_SIZE = 32;
constexpr unsigned MAX_PLAYLIST_SIZE = 129;
constexpr unsigned MAX_USERNAME_SIZE = 64;
constexpr unsigned MAX_PLAYLIST_COLLECTION_SIZE = 64;

enum class Genre {
  POP, ROCK, METAL, JAZZ, CLASSICAL, INDIE
};

char const *toString(Genre genre) {
  switch (genre) {
    case Genre::POP: return "pop";
    case Genre::ROCK: return "rock";
    case Genre::METAL: return "metal";
    case Genre::JAZZ: return "jazz";
    case Genre::CLASSICAL: return "classical";
    case Genre::INDIE: return "indie";
  }

  return "unknown genre";
}

struct Song {
  char title[MAX_SONG_TITLE_SIZE];
  char artist[MAX_SONG_ARTIST_SIZE];
  unsigned duration;
  unsigned timesListened;
  Genre genre;
};

struct HoursMinutesSeconds {
  unsigned hours, minutes, seconds;
};

HoursMinutesSeconds toHms(unsigned seconds) {
  HoursMinutesSeconds hms;

  hms.hours = seconds / 3600;
  unsigned rem1 = seconds % 3600;

  hms.minutes = rem1 / 60;

  hms.seconds = rem1 % 60;

  return hms;
}

char const *padIfSingleDigit(unsigned x) {
  if (x < 10) return "0";
  return "";
}

void print(HoursMinutesSeconds const &hms) {
  std::cout << padIfSingleDigit(hms.hours) << hms.hours << ':';
  std::cout << padIfSingleDigit(hms.minutes) << hms.minutes << ':';
  std::cout << padIfSingleDigit(hms.seconds) << hms.seconds;
}

void print(Song const &song) {
  std::cout << "Title: " << song.title << '\n';
  std::cout << "Artist: " << song.artist << '\n';
  std::cout << "Genre: " << toString(song.genre) << '\n';
  std::cout << "Duration: "; print(toHms(song.duration)); std::cout << '\n';
  std::cout << "Times listened: " << song.timesListened << '\n';
}

enum class Mode {
  NORMAL, SHUFFLE
};

struct Playlist {
  char name[MAX_PLAYLIST_NAME_SIZE];
  Song songs[MAX_PLAYLIST_SIZE];
  unsigned currSize;
  unsigned currSong;
  Mode mode;
};

Playlist mkPlaylist() {
  return Playlist{ .name = "no name", .currSize = 0, .currSong = 0, .mode = Mode::NORMAL };
}

bool eqSongs(Song const &lhs, Song const &rhs) {
  return !strcmp(lhs.title, rhs.title) &&
         !strcmp(lhs.artist, rhs.artist) &&
         lhs.duration == rhs.duration &&
         lhs.genre == rhs.genre;
}

bool containsSong(Song const &song, Playlist const &playlist) {
  for (unsigned i = 0; i < playlist.currSize; ++i)

    if (eqSongs(playlist.songs[i], song))
      return true;

  return false;
}

bool addSong(Song const &song, Playlist &playlist) {
  if (playlist.currSize >= MAX_PLAYLIST_SIZE)
    return false;

  if (containsSong(song, playlist))
    return false;

  playlist.songs[playlist.currSize] = song;
  playlist.currSize++;

  return true;
}

unsigned totalDuration(Playlist const &playlist) {
  unsigned dur = 0;

  for (unsigned i = 0; i < playlist.currSize; ++i)
    dur += playlist.songs[i].duration;

  return dur;
}

Playlist filterByGenre(Genre genre, Playlist const &playlist) {
  Playlist result = mkPlaylist();

  for (unsigned i = 0; i < playlist.currSize; ++i)

    if (playlist.songs[i].genre == genre)
      result.songs[result.currSize++] = playlist.songs[i];

  return result;
}

bool removeSong(Song const &song, Playlist &playlist) {
  unsigned i = 0;

  while (i < playlist.currSize) {
    if (eqSongs(playlist.songs[i], song))
      break;

    i++;
  }

  if (i >= playlist.currSize)
    return false;

  // изместваме песните с една позциия наляво
  while (i < playlist.currSize - 1) {
    playlist.songs[i] = playlist.songs[i+1];
    i++;
  }

  playlist.currSize--;

  return true;
}

void playSong(Playlist const &playlist) {
  if (playlist.currSize == 0) {
    std::cout << "Playlist " << playlist.name << " is empty\n";
    return;
  }

  std::cout << "Now playing...\n";
  print(playlist.songs[playlist.currSong]);
  std::cout << '\n';
}

void nextSong(Playlist &playlist) {
  if (playlist.currSize == 0)
    return;

  switch (playlist.mode) {

    case Mode::NORMAL:
      playlist.currSong = (playlist.currSong + 1) % playlist.currSize;
      return;

    case Mode::SHUFFLE:
      playlist.currSong = rand() % playlist.currSize;
  }
}

// приемаме, че едно слушане на една песен в плейлиста означава
// едно негово слушане
unsigned timesListenedToPlaylist(Playlist const &playlist) {
  unsigned result = 0;

  for (unsigned i = 0; i < playlist.currSize; ++i)
    result += playlist.songs[i].timesListened;

  return result;
}

struct Profile {
  char username[MAX_USERNAME_SIZE];
  Playlist playlists[MAX_PLAYLIST_COLLECTION_SIZE];
  unsigned currPlaylistSize;
};

struct Pair {
  unsigned timesListened, index;
};

bool cmp(Pair const &lhs, Pair const &rhs) {
  return lhs.timesListened < rhs.timesListened;
}

void sortPlaylists(Pair *playlistInfo, unsigned size) {
  for (unsigned i = 1; i < size; ++i) {

    Pair key = playlistInfo[i];
    int j = i - 1;

    while (j >= 0 && cmp(playlistInfo[j], key)) {
      playlistInfo[j+1] = playlistInfo[j];
      j--;
    }

    playlistInfo[j+1] = key;
  }
}

void print(Profile const &profile) {
  std::cout << "Username: " << profile.username << '\n';

  Pair playlistInfo[MAX_PLAYLIST_COLLECTION_SIZE];
  for (unsigned i = 0; i < profile.currPlaylistSize; ++i)
    playlistInfo[i] = {timesListenedToPlaylist(profile.playlists[i]), i};

  sortPlaylists(playlistInfo, profile.currPlaylistSize);

  for (unsigned i = 0; i < profile.currPlaylistSize; ++i) {
    unsigned idx = playlistInfo[i].index;
    std::cout << i+1 << ". " << profile.playlists[idx].name << '\n';
  }
}

int main() {
  // генерирано с любезното съдейстиве на ChatGPT :)

  srand(time(nullptr));

  Song s1{};
  std::strcpy(s1.title, "Octavarium");
  std::strcpy(s1.artist, "Dream Theater");
  s1.duration = 1440;
  s1.timesListened = 12;
  s1.genre = Genre::METAL;

  Song s2{};
  std::strcpy(s2.title, "Between the Bars");
  std::strcpy(s2.artist, "Elliott Smith");
  s2.duration = 141;
  s2.timesListened = 8;
  s2.genre = Genre::INDIE;

  Song s3{};
  std::strcpy(s3.title, "Gabriela");
  std::strcpy(s3.artist, "KATSEYE");
  s3.duration = 178;
  s3.timesListened = 5;
  s3.genre = Genre::POP;

  Song s4{};
  std::strcpy(s4.title, "Verklarte Nacht");
  std::strcpy(s4.artist, "Arnold Schoenberg");
  s4.duration = 1800;
  s4.timesListened = 3;
  s4.genre = Genre::CLASSICAL;

  Song s5{};
  std::strcpy(s5.title, "Stateside");
  std::strcpy(s5.artist, "Zara Larsson");
  s5.duration = 165;
  s5.timesListened = 6;
  s5.genre = Genre::POP;

  Song s6{};
  std::strcpy(s6.title, "Piano Concerto No. 2");
  std::strcpy(s6.artist, "Sergei Rachmaninoff");
  s6.duration = 2100;
  s6.timesListened = 4;
  s6.genre = Genre::CLASSICAL;

  Song s7{};
  std::strcpy(s7.title, "Drift");
  std::strcpy(s7.artist, "Kollapse");
  s7.duration = 320;
  s7.timesListened = 1;
  s7.genre = Genre::METAL;

  Song s8{};
  std::strcpy(s8.title, "Vengo dalla Luna");
  std::strcpy(s8.artist, "Maneskin");
  s8.duration = 238;
  s8.timesListened = 4;
  s8.genre = Genre::ROCK;

  Song s9{};
  std::strcpy(s9.title, "Dance of the Sugar Plum Fairy");
  std::strcpy(s9.artist, "Pyotr Ilyich Tchaikovsky");
  s9.duration = 120;
  s9.timesListened = 3;
  s9.genre = Genre::CLASSICAL;

  Playlist p = mkPlaylist();
  std::strcpy(p.name, "playlist #1");

  addSong(s1, p);
  addSong(s2, p);
  addSong(s3, p);
  addSong(s4, p);
  addSong(s5, p);
  addSong(s6, p);
  addSong(s7, p);
  addSong(s8, p);
  addSong(s9, p);

  std::cout << "Total duration: ";
  print(toHms(totalDuration(p)));
  std::cout << "\n\n";

  playSong(p);
  nextSong(p);
  playSong(p);

  Playlist metalOnly = filterByGenre(Genre::METAL, p);
  std::strcpy(metalOnly.name, "metal");

  Playlist classicalOnly = filterByGenre(Genre::CLASSICAL, p);
  std::strcpy(classicalOnly.name, "classical");

  Playlist popOnly = filterByGenre(Genre::POP, p);
  std::strcpy(popOnly.name, "pop");

  Profile profile{};
  std::strcpy(profile.username, "nico");

  profile.playlists[0] = p;
  profile.playlists[1] = metalOnly;
  profile.playlists[2] = classicalOnly;
  profile.playlists[3] = popOnly;
  profile.currPlaylistSize = 4;

  std::cout << "\nProfile info:\n";
  print(profile);

  return 0;
}
